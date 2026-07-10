/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 10/07/2026
   Ultima modificacion: 10/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de WebServer
*/
#include "ui/WebServer.h"
#include "exceptions/SimulatorException.h"
#include "algorithms/FirstFit.h"
#include "algorithms/BestFit.h"
#include "algorithms/WorstFit.h"
#include "httplib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

WebServer::WebServer()
{
    this->manager = nullptr;
    this->port = 8080;
}

WebServer::WebServer(MemoryManager* manager, int port)
{
    this->manager = manager;
    this->port = port;
}

WebServer::~WebServer()
{
    
}

std::string WebServer::escapeJson(const std::string& text) const
{
    
    std::string result;
    for (size_t i = 0; i < text.size(); i++)
    {
        char currentChar = text.at(i);
        if (currentChar == '"')
        {
            result = result + "\\\"";
        }
        else if (currentChar == '\n')
        {
            result = result + "\\n";
        }
        else
        {
            result = result + currentChar;
        }
    }
    return result;
}

std::string WebServer::buildStateJson() const
{
    const std::vector<MemoryBlock>& blocks = this->manager->getBlocks();
    std::stringstream json;

    json << "{\"blocks\":[";
    for (size_t i = 0; i < blocks.size(); i++)
    {
        const MemoryBlock& currentBlock = blocks.at(i);
        if (i > 0)
        {
            json << ",";
        }
        json << "{\"index\":" << i;
        json << ",\"startAddress\":" << currentBlock.getStartAddress();
        json << ",\"size\":" << currentBlock.getSize();
        json << ",\"free\":" << (currentBlock.isFree() ? "true" : "false");

        if (!currentBlock.isFree() && currentBlock.getProcess() != nullptr)
        {
            json << ",\"processId\":" << currentBlock.getProcess()->getId();
            json << ",\"processName\":\"" << this->escapeJson(currentBlock.getProcess()->getName()) << "\"";
        }
        json << "}";
    }
    json << "],\"externalFragmentation\":" << this->manager->calculateExternalFragmentation();
    json << ",\"internalFragmentation\":" << this->manager->calculateInternalFragmentation();
    json << "}";

    return json.str();
}

std::string WebServer::buildErrorJson(const std::string& message) const
{
    std::stringstream json;
    json << "{\"error\":\"" << this->escapeJson(message) << "\"}";
    return json.str();
}

void WebServer::start()
{
    httplib::Server server;
    

    server.set_default_headers({{"Access-Control-Allow-Origin", "*"}});

    server.set_mount_point("/", "allocation_simulator/web");

    server.Get("/api/state", [this](const httplib::Request&, httplib::Response& res)
    {
        res.set_content(this->buildStateJson(), "application/json");
    });

    server.Post("/api/reset", [this](const httplib::Request&, httplib::Response& res)
    {
        this->manager->reset();
        res.set_content(this->buildStateJson(), "application/json");
    });


    

    server.Post("/api/process", [this](const httplib::Request& req, httplib::Response& res)
    {
        std::string name = req.get_param_value("name");
        std::string sizeText = req.get_param_value("size");

        int requestedSize = 0;
        try
        {
            requestedSize = std::stoi(sizeText);
        }
        catch (const std::exception&)
        {
            res.status = 400;
            res.set_content(this->buildErrorJson("size debe ser un numero valido"), "application/json");
            return;
        }

        if (!Process::isValidData(requestedSize))
        {
            res.status = 400;
            res.set_content(this->buildErrorJson("El tamano debe ser mayor que cero"), "application/json");
            return;
        }

        //El id lo genera el manager
        int assignedId = this->manager->generateProcessId();
        Process newProcess(assignedId, name, requestedSize);
        try
        {
            this->manager->allocateProcess(newProcess);
            res.set_content(this->buildStateJson(), "application/json");
        }
        catch (const SimulatorException& exceptionCaught)
        {
            res.status = 409;
            res.set_content(this->buildErrorJson(exceptionCaught.what()), "application/json");
        }
    });

    server.Post("/api/process/release", [this](const httplib::Request& req, httplib::Response& res)
    {
        std::string idText = req.get_param_value("id");
        int id = 0;
        try
        {
            id = std::stoi(idText);
        }
        catch (const std::exception&)
        {
            res.status = 400;
            res.set_content(this->buildErrorJson("id debe ser un numero valido"), "application/json");
            return;
        }

        try
        {
            this->manager->releaseProcess(id);
            res.set_content(this->buildStateJson(), "application/json");
        }
        catch (const SimulatorException& exceptionCaught)
        {
            res.status = 404;
            res.set_content(this->buildErrorJson(exceptionCaught.what()), "application/json");
        }
    });

    server.Post("/api/strategy", [this](const httplib::Request& req, httplib::Response& res)
    {
        std::string strategyName = req.get_param_value("strategy");

        if (strategyName == "first")
        {
            this->manager->setAllocation(new FirstFit());
        }
        else if (strategyName == "best")
        {
            this->manager->setAllocation(new BestFit());
        }
        else if (strategyName == "worst")
        {
            this->manager->setAllocation(new WorstFit());
        }
        else
        {
            res.status = 400;
            res.set_content(this->buildErrorJson("Estrategia invalida, use first, best o worst"), "application/json");
            return;
        }

        res.set_content(this->buildStateJson(), "application/json");
    });

    server.Post("/api/load-file", [this](const httplib::Request& req, httplib::Response& res)
    {
        std::string fileName = req.get_param_value("fileName");
        std::string fullPath = "data/allocation/" + fileName;

        std::vector<Command> commands;
        try
        {
            commands = this->fileReader.readCommands(fullPath);
        }
        catch (const SimulatorException& exceptionCaught)
        {
            res.status = 400;
            res.set_content(this->buildErrorJson(exceptionCaught.what()), "application/json");
            return;
        }

        std::map<std::string, int> labelToId;
        std::stringstream log;

        for (size_t i = 0; i < commands.size(); i++)
        {
            const Command& currentCommand = commands.at(i);

            if (currentCommand.getType() == CommandType::CREATE)
            {
                //El id lo genera el manager
                int assignedId = this->manager->generateProcessId();
                

                Process newProcess(assignedId, currentCommand.getLabel(), currentCommand.getSize());
                try
                {
                    this->manager->allocateProcess(newProcess);
                    labelToId[currentCommand.getLabel()] = assignedId;
                    log << "Proceso " << currentCommand.getLabel() << " creado correctamente." << std::endl;
                }
                catch (const SimulatorException& exceptionCaught)
                {
                    log << "Error al crear el proceso " << currentCommand.getLabel() << ": " << exceptionCaught.what() << std::endl;
                }
            }
            else
            {
                std::map<std::string, int>::iterator labelIterator = labelToId.find(currentCommand.getLabel());
                if (labelIterator == labelToId.end())
                {
                    log << "No se encontro el proceso " << currentCommand.getLabel() << " para liberar." << std::endl;
                    continue;
                }

                try
                {
                    this->manager->releaseProcess(labelIterator->second);
                    log << "Proceso " << currentCommand.getLabel() << " liberado correctamente." << std::endl;
                }
                catch (const SimulatorException& exceptionCaught)
                {
                    log << "Error al liberar el proceso " << currentCommand.getLabel() << ": " << exceptionCaught.what() << std::endl;
                }
            }
        }

        std::string baseName = fileName;
        size_t extensionPosition = baseName.rfind(".txt");
        if (extensionPosition != std::string::npos && extensionPosition == baseName.size() - 4)
        {
            baseName = baseName.substr(0, extensionPosition);
        }
        std::ofstream outputFile("allocation_simulator/tests/" + baseName + "_output.txt");
        if (outputFile.is_open())
        {
            outputFile << log.str();
            outputFile.close();
        }

        std::stringstream json;
        json << "{\"log\":\"" << this->escapeJson(log.str()) << "\",";
        json << "\"state\":" << this->buildStateJson() << "}";

        res.set_content(json.str(), "application/json");
    });

    std::cout << "Servidor web de allocation_simulator escuchando en el puerto " << this->port << std::endl;
    server.listen("0.0.0.0", this->port);
}