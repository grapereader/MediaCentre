#ifndef HTTPUTILS_H
#define HTTPUTILS_H

namespace vmc
{
    namespace util
    {
        char const *getStatus(int code)
        {
            if (code == 200) return "OK";
            if (code == 201) return "Created";
            if (code == 202) return "Accepted";
            if (code == 204) return "No Content";
            if (code == 206) return "Partial Content";

            if (code == 301) return "Moved Permanently";
            if (code == 302) return "Found";
            if (code == 303) return "See Other";
            if (code == 304) return "Not Modified";
            if (code == 307) return "Temporary Redirect";
            if (code == 308) return "Permanent Redirect";

            if (code == 400) return "Bad Request";
            if (code == 401) return "Unauthorized";
            if (code == 403) return "Forbidden";
            if (code == 404) return "Not Found";
            if (code == 405) return "Method Not Allowed";
            if (code == 406) return "Not Acceptable";
            if (code == 408) return "Request Timeout";
            if (code == 409) return "Conflict";
            if (code == 411) return "Length Required";
            if (code == 412) return "Precondition Failed";
            if (code == 413) return "Payload Too Large";
            if (code == 415) return "Unsupported Media Type";

            if (code == 500) return "Internal Server Error";
            if (code == 501) return "Not Implemented";
            if (code == 502) return "Bad Gateway";
            if (code == 503) return "Service Unavailable";
            if (code == 505) return "HTTP Version Not Supported";
            if (code == 507) return "Insufficient Storage";

            return "";
        }
    }
}

#endif
