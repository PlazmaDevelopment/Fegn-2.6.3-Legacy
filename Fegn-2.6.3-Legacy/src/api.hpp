#ifndef FEGN_API_HPP
#define FEGN_API_HPP

#include <string>
#include <memory>
#include <map>

namespace Fegn {
    // API yanıt
    class ApiResponse {
    public:
        std::string data;
        int status;
        std::map<std::string, std::string> headers;
        
        ApiResponse(const std::string& data, int status)
            : data(data), status(status) {}
    };
    
    // API istek
    class ApiRequest {
    public:
        std::string endpoint;
        std::map<std::string, std::string> headers;
        std::string body;
        
        ApiRequest(const std::string& endpoint)
            : endpoint(endpoint) {}
    };
    
    // API yöneticisi
    class ApiManager {
    private:
        std::string baseUrl;
        
    public:
        ApiManager(const std::string& baseUrl)
            : baseUrl(baseUrl) {}
        
        // GET isteği
        std::shared_ptr<ApiResponse> get(const std::string& endpoint) {
            auto request = std::make_shared<ApiRequest>(endpoint);
            return processRequest(request);
        }
        
        // POST isteği
        std::shared_ptr<ApiResponse> post(const std::string& endpoint, const std::string& data) {
            auto request = std::make_shared<ApiRequest>(endpoint);
            request->body = data;
            return processRequest(request);
        }
        
    private:
        std::shared_ptr<ApiResponse> processRequest(std::shared_ptr<ApiRequest> request) {
            // İstek işleme
            return std::make_shared<ApiResponse>("", 200);
        }
    };
    
    // API istemcisi
    class ApiClient {
    private:
        std::shared_ptr<ApiManager> manager;
        
    public:
        ApiClient(std::shared_ptr<ApiManager> manager)
            : manager(manager) {}
        
        std::shared_ptr<ApiResponse> get(const std::string& endpoint) {
            return manager->get(endpoint);
        }
        
        std::shared_ptr<ApiResponse> post(const std::string& endpoint, const std::string& data) {
            return manager->post(endpoint, data);
        }
    };
}

#endif // FEGN_API_HPP
