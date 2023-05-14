#include "HttpRequest.h"

const QString HttpRequest::HTTP_1_0 = "HTTP/1.0";
const QString HttpRequest::HTTP_1_1 = "HTTP/1.1";

const QString HttpRequest::GET_VERB = "GET";
const QString HttpRequest::POST_VERB = "POST";
const QString HttpRequest::PUT_VERB = "PUT";
const QString HttpRequest::DELETE_VERB = "DELETE";


/*!
 * \brief Constructor of the class
 */
HttpRequest::HttpRequest()
{

}


HttpRequest HttpRequest::create(QString clientRequest)
{
    HttpRequest *request = new HttpRequest();
    request->requestWellFormed = HttpRequest::isValidRequest(clientRequest);
    if(request->isRequestWellFormed()) {
        request->httpVerb = request->readHttpVerb(clientRequest);
        request->requestPath = request->readRequestPath(
                    request->httpVerb, clientRequest);
    }
    return *request;
}

/*!
 * \brief Validates if the request is valid
 * \param clientRequest
 * \return
 */
bool HttpRequest::isValidRequest(QString clientRequest)
{
    bool requestIsInvalid = false;
    if(!clientRequest.isNull() && !clientRequest.isEmpty()) {
        if(HttpRequest::hasHttpRequestVerb(clientRequest)
                && HttpRequest::hasHttpVersion(clientRequest))
        {
            return true;
        }
    }
    return requestIsInvalid;
}




/*!
 * \brief Check if the request contians a http Verb (POST, GET)
 * \param request
 * \return
 */
bool HttpRequest::hasHttpRequestVerb(QString request)
{
    // LATER INCLUDE MORE VERBS
    if(request.startsWith(HttpRequest::GET_VERB) ||
        request.startsWith(HttpRequest::POST_VERB))
    {
      return true;
    }
    return false;
}

/*!
 * \brief Check if the request contains the HTTP version
 * \param request
 * \return
 */
bool HttpRequest::hasHttpVersion(QString request)
{
    // LATER INCLUDE MORE VERBS
    if(request.contains(HttpRequest::HTTP_1_0) ||
        request.contains(HttpRequest::HTTP_1_1))
    {
      return true;
    }
    return false;
}

/*!
 * \brief Read the http header
 * \param clientRequest
 * \return
 */
HttpVerb HttpRequest::readHttpVerb(QString clientRequest)
{
    if(clientRequest.startsWith(GET_VERB))
    {
        return GET;
    }
    else if(clientRequest.startsWith(POST_VERB))
    {
        return POST;
    }
    else
    {
        return OTHER;
    }
}


/*!
 * \brief Reads the Http Verb of the current request
 * \return
 */
QString HttpRequest::getHttpVerbAsString()
{
    return getHttpVerbAsString(this->httpVerb);
}

/*!
 * \brief Gets the string of the HttpVerb
 * \return
 */
QString HttpRequest::getHttpVerbAsString(HttpVerb)
{
    switch (httpVerb) {
    case GET:
        return HttpRequest::GET_VERB;
    case POST:
        return HttpRequest::POST_VERB;
    case PUT:
        return HttpRequest::PUT_VERB;
    case DELETE:
        return HttpRequest::DELETE_VERB;
    default:
        return HttpRequest::GET_VERB;
    }
}

/*!
 * \brief HttpRequest::readRequestPath
 * \param httpVerb
 * \param clientRequest
 * \return
 */
QString HttpRequest::readRequestPath(HttpVerb httpVerb, QString clientRequest)
{
    QString verb = getHttpVerbAsString(httpVerb);
    int verbSize = verb.size();
    // Removes the get
    int beginHttpVersionIndex = clientRequest.indexOf("HTTP/");
    int numberOfChars = beginHttpVersionIndex - verbSize;
    QString path = clientRequest.mid(verbSize, numberOfChars);
    return path.trimmed();
}


bool HttpRequest::isRequestWellFormed()
{
    return this->requestWellFormed;
}


HttpVerb HttpRequest::getHttpVerb() {
    return this->httpVerb;
}

QString HttpRequest::getRequestPath() {
    return this->requestPath;
}
