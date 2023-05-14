#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "SiteRepository.h"


class HttpRequestHandler
{
public:
    HttpRequestHandler(SiteRepository *site);
    HttpResponse processRequest(HttpRequest request);

private:
    SiteRepository *siteRepository;
};

#endif // REQUESTHANDLER_H
