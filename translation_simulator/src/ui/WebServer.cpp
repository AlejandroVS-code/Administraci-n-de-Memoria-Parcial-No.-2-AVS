/* Autor: Alejandro Valencia Sandoval
   Correo: Alejandro.Valencia.Sandoval@correounivalle.edu.co
   Fecha de creacion: 10/07/2026
   Ultima modificacion: 10/07/2026
   Version: 1.0
   Licencia: Uso academico, Universidad del Valle
   Descripcion: Implementacion de WebServer para Implementacion 2,
   expone una API HTTP sobre MemoryTranslator como interfaz grafica
   adicional al menu de consola
*/
#include "ui/WebServer.h"
#include "exceptions/TranslatorException.h"
#include "algorithms/PagingStrategy.h"
#include "algorithms/SegmentationStrategy.h"
#include "httplib.h"
#include <iostream>
#include <fstream>
#include <sstream>

WebServer::WebServer()
{
    this->translator = nullptr;
    this->port = 8081;
}

WebServer::WebServer(MemoryTranslator* translator, int port)
{
    this->translator = translator;
    this->port = port;
}

WebServer::~WebServer()
{
    //No hago delete de translator porque este servidor no es dueno de ese objeto
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
    std::stringstream json;

    //Marcos de memoria fisica
    const std::vector<Frame>& frames = this->translator->getFrames();
    json << "{\"frames\":[";
    for (size_t i = 0; i < frames.size(); i++)
    {
        const Frame& currentFrame = frames.at(i);
        if (i > 0)
        {
            json << ",";
        }
        json << "{\"frameNumber\":" << currentFrame.getFrameNumber();
        json << ",\"free\":" << (currentFrame.isFree() ? "true" : "false") << "}";
    }
    json << "],";

    //Tabla de paginas
    const std::vector<Page>& pages = this->translator->getPageTable().getEntries();
    json << "\"pages\":[";
    for (size_t i = 0; i < pages.size(); i++)
    {
        const Page& currentPage = pages.at(i);
        if (i > 0)
        {
            json << ",";
        }
        json << "{\"pageNumber\":" << currentPage.getPageNumber();
        json << ",\"frameNumber\":" << currentPage.getFrameNumber();
        json << ",\"valid\":" << (currentPage.isValid() ? "true" : "false") << "}";
    }
    json << "],";

    //Tabla de segmentos
    const std::vector<Segment>& segments = this->translator->getSegmentTable().getEntries();
    json << "\"segments\":[";
    for (size_t i = 0; i < segments.size(); i++)
    {
        const Segment& currentSegment = segments.at(i);
        if (i > 0)
        {
            json << ",";
        }
        json << "{\"segmentNumber\":" << currentSegment.getSegmentNumber();
        json << ",\"baseAddress\":" << currentSegment.getBaseAddress();
        json << ",\"limit\":" << currentSegment.getLimit() << "}";
    }
    json << "]}";

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

    //Sirvo el frontend estatico (index.html, css, js) desde esta carpeta
    server.set_mount_point("/", "./translation_simulator/web");

    server.Get("/api/state", [this](const httplib::Request&, httplib::Response& res)
    {
        res.set_content(this->buildStateJson(), "application/json");
    });

    server.Post("/api/reset", [this](const httplib::Request&, httplib::Response& res)
    {
        this->translator->reset();
        res.set_content(this->buildStateJson(), "application/json");
    });



    server.Post("/api/page", [this](const httplib::Request& req, httplib::Response& res)
    {
        int pageNumber = 0;
        int frameNumber = 0;
        try
        {
            pageNumber = std::stoi(req.get_param_value("pageNumber"));
            frameNumber = std::stoi(req.get_param_value("frameNumber"));
        }
        catch (const std::exception&)
        {
            res.status = 400;
            res.set_content(this->buildErrorJson("pageNumber y frameNumber deben ser numeros validos"), "application/json");
            return;
        }

        try
        {
            this->translator->loadPageMapping(pageNumber, frameNumber);
            res.set_content(this->buildStateJson(), "application/json");
        }
        catch (const TranslatorException& exceptionCaught)
        {
            res.status = 400;
            res.set_content(this->buildErrorJson(exceptionCaught.what()), "application/json");
        }
    });

    server.Post("/api/segment", [this](const httplib::Request& req, httplib::Response& res)
    {
        int segmentNumber = 0;
        int baseAddress = 0;
        int limit = 0;
        try
        {
            segmentNumber = std::stoi(req.get_param_value("segmentNumber"));
            baseAddress = std::stoi(req.get_param_value("baseAddress"));
            limit = std::stoi(req.get_param_value("limit"));
        }
        catch (const std::exception&)
        {
            res.status = 400;
            res.set_content(this->buildErrorJson("segmentNumber, baseAddress y limit deben ser numeros validos"), "application/json");
            return;
        }

        try
        {
            this->translator->loadSegment(segmentNumber, baseAddress, limit);
            res.set_content(this->buildStateJson(), "application/json");
        }
        catch (const TranslatorException& exceptionCaught)
        {
            res.status = 400;
            res.set_content(this->buildErrorJson(exceptionCaught.what()), "application/json");
        }
    });

    server.Post("/api/translate", [this](const httplib::Request& req, httplib::Response& res)
    {
        int rawValue = 0;
        try
        {
            rawValue = std::stoi(req.get_param_value("address"));
        }
        catch (const std::exception&)
        {
            res.status = 400;
            res.set_content(this->buildErrorJson("address debe ser un numero valido"), "application/json");
            return;
        }

        if (!VirtualAddress::isValidData(rawValue))
        {
            res.status = 400;
            res.set_content(this->buildErrorJson("La direccion no puede ser negativa"), "application/json");
            return;
        }

        VirtualAddress virtualAddress(rawValue);
        try
        {
            PhysicalAddress physicalAddress = this->translator->translateAddress(virtualAddress);
            std::stringstream json;
            json << "{\"physicalAddress\":" << physicalAddress.getValue() << "}";
            res.set_content(json.str(), "application/json");
        }
        catch (const TranslatorException& exceptionCaught)
        {
            res.status = 400;
            res.set_content(this->buildErrorJson(exceptionCaught.what()), "application/json");
        }
    });

    server.Post("/api/strategy", [this](const httplib::Request& req, httplib::Response& res)
    {
        std::string strategyName = req.get_param_value("strategy");

        if (strategyName == "paging")
        {
            int pageSize = 0;
            try
            {
                pageSize = std::stoi(req.get_param_value("pageSize"));
            }
            catch (const std::exception&)
            {
                res.status = 400;
                res.set_content(this->buildErrorJson("pageSize debe ser un numero valido"), "application/json");
                return;
            }
            this->translator->setStrategy(new PagingStrategy(pageSize));
        }
        else if (strategyName == "segmentation")
        {
            int maxSegmentSize = 0;
            try
            {
                maxSegmentSize = std::stoi(req.get_param_value("maxSegmentSize"));
            }
            catch (const std::exception&)
            {
                res.status = 400;
                res.set_content(this->buildErrorJson("maxSegmentSize debe ser un numero valido"), "application/json");
                return;
            }
            this->translator->setStrategy(new SegmentationStrategy(maxSegmentSize));
        }
        else
        {
            res.status = 400;
            res.set_content(this->buildErrorJson("Estrategia invalida, use paging o segmentation"), "application/json");
            return;
        }

        res.set_content(this->buildStateJson(), "application/json");
    });

    server.Post("/api/load-file", [this](const httplib::Request& req, httplib::Response& res)
    {
        std::string fileName = req.get_param_value("fileName");
        std::string fullPath = "data/translation/" + fileName;

        std::vector<TranslationCommand> commands;
        try
        {
            commands = this->fileReader.readCommands(fullPath);
        }
        catch (const TranslatorException& exceptionCaught)
        {
            res.status = 400;
            res.set_content(this->buildErrorJson(exceptionCaught.what()), "application/json");
            return;
        }

        std::stringstream log;

        for (size_t i = 0; i < commands.size(); i++)
        {
            const TranslationCommand& currentCommand = commands.at(i);

            if (currentCommand.getType() == TranslationCommandType::MAP_PAGE)
            {
                try
                {
                    this->translator->loadPageMapping(currentCommand.getFirstValue(), currentCommand.getSecondValue());
                    log << "Mapeo cargado: pagina " << currentCommand.getFirstValue() << " -> marco " << currentCommand.getSecondValue() << std::endl;
                }
                catch (const TranslatorException& exceptionCaught)
                {
                    log << "Error al mapear pagina " << currentCommand.getFirstValue() << ": " << exceptionCaught.what() << std::endl;
                }
            }
            else if (currentCommand.getType() == TranslationCommandType::MAP_SEGMENT)
            {
                try
                {
                    this->translator->loadSegment(currentCommand.getFirstValue(), currentCommand.getSecondValue(), currentCommand.getThirdValue());
                    log << "Segmento cargado: " << currentCommand.getFirstValue() << " base=" << currentCommand.getSecondValue() << " limite=" << currentCommand.getThirdValue() << std::endl;
                }
                catch (const TranslatorException& exceptionCaught)
                {
                    log << "Error al cargar segmento " << currentCommand.getFirstValue() << ": " << exceptionCaught.what() << std::endl;
                }
            }
            else
            {
                VirtualAddress virtualAddress(currentCommand.getFirstValue());
                try
                {
                    PhysicalAddress physicalAddress = this->translator->translateAddress(virtualAddress);
                    log << "Traduccion: VA=" << virtualAddress.getValue() << " -> PA=" << physicalAddress.getValue() << std::endl;
                }
                catch (const TranslatorException& exceptionCaught)
                {
                    log << "Error al traducir VA=" << virtualAddress.getValue() << ": " << exceptionCaught.what() << std::endl;
                }
            }
        }

        std::string baseName = fileName;
        size_t extensionPosition = baseName.rfind(".txt");
        if (extensionPosition != std::string::npos && extensionPosition == baseName.size() - 4)
        {
            baseName = baseName.substr(0, extensionPosition);
        }
        std::ofstream outputFile("translation_simulator/tests/" + baseName + "_output.txt");
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

    std::cout << "Servidor web de translation_simulator escuchando en el puerto " << this->port << std::endl;
    server.listen("0.0.0.0", this->port);
}