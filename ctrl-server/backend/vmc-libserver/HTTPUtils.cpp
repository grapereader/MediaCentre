#include "HTTPUtils.h"

namespace vmc
{
    namespace util
    {
        char const *getStatus(int code)
        {
            switch (code)
            {
                case 200: return "OK";
                case 201: return "Created";
                case 202: return "Accepted";
                case 204: return "No Content";
                case 206: return "Partial Content";

                case 301: return "Moved Permanently";
                case 302: return "Found";
                case 303: return "See Other";
                case 304: return "Not Modified";
                case 307: return "Temporary Redirect";
                case 308: return "Permanent Redirect";

                case 400: return "Bad Request";
                case 401: return "Unauthorized";
                case 403: return "Forbidden";
                case 404: return "Not Found";
                case 405: return "Method Not Allowed";
                case 406: return "Not Acceptable";
                case 408: return "Request Timeout";
                case 409: return "Conflict";
                case 411: return "Length Required";
                case 412: return "Precondition Failed";
                case 413: return "Payload Too Large";
                case 415: return "Unsupported Media Type";

                case 500: return "Internal Server Error";
                case 501: return "Not Implemented";
                case 502: return "Bad Gateway";
                case 503: return "Service Unavailable";
                case 505: return "HTTP Version Not Supported";
                case 507: return "Insufficient Storage";
            }
            return "";
        }

        void redirect(HTTPRequest &req, std::string const &location)
        {
            req.getResponseHeaders()->put("Location", location);
            req.sendResponseHeaders(307);
        }

        void sendJSON(HTTPRequest &req, nlohmann::json const &json)
        {
            std::string jsonString  = json.dump(4);
            req.getResponseHeaders()->put("Content-Length", jsonString.length());
            req.getResponseHeaders()->put("Content-Type", "application/json");
            req.sendResponseHeaders(200);
            req.getStream() << jsonString;
        }
    }
}
