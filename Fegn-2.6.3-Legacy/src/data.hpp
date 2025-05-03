#ifndef FEGN_DATA_HPP
#define FEGN_DATA_HPP

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace Fegn {
    // Veri öğesi
    class DataItem {
    public:
        std::map<std::string, std::string> data;
        std::chrono::steady_clock::time_point timestamp;
        
        DataItem(const std::map<std::string, std::string>& data)
            : data(data), timestamp(std::chrono::steady_clock::now()) {}
    };
    
    // Veri yöneticisi
    class DataManager {
    private:
        std::map<std::string, std::vector<std::shared_ptr<DataItem>>> stores;
        
    public:
        // Veri ekle
        void add(const std::string& storeName, const std::map<std::string, std::string>& data) {
            auto item = std::make_shared<DataItem>(data);
            stores[storeName].push_back(item);
        }
        
        // Veri al
        std::vector<std::shared_ptr<DataItem>> get(const std::string& storeName, const std::map<std::string, std::string>& filters) {
            std::vector<std::shared_ptr<DataItem>> results;
            
            if (stores.find(storeName) != stores.end()) {
                for (auto& item : stores[storeName]) {
                    bool matches = true;
                    for (auto& filter : filters) {
                        if (item->data[filter.first] != filter.second) {
                            matches = false;
                            break;
                        }
                    }
                    if (matches) {
                        results.push_back(item);
                    }
                }
            }
            
            return results;
        }
        
        // Veri sil
        void remove(const std::string& storeName, const std::map<std::string, std::string>& filters) {
            if (stores.find(storeName) != stores.end()) {
                auto& items = stores[storeName];
                items.erase(
                    std::remove_if(
                        items.begin(),
                        items.end(),
                        [&filters](const std::shared_ptr<DataItem>& item) {
                            for (auto& filter : filters) {
                                if (item->data[filter.first] != filter.second) {
                                    return false;
                                }
                            }
                            return true;
                        }
                    ),
                    items.end()
                );
            }
        }
    };
    
    // Veri istemcisi
    class DataClient {
    private:
        std::shared_ptr<DataManager> manager;
        
    public:
        DataClient(std::shared_ptr<DataManager> manager)
            : manager(manager) {}
        
        void add(const std::string& storeName, const std::map<std::string, std::string>& data) {
            manager->add(storeName, data);
        }
        
        std::vector<std::shared_ptr<DataItem>> get(const std::string& storeName, const std::map<std::string, std::string>& filters) {
            return manager->get(storeName, filters);
        }
        
        void remove(const std::string& storeName, const std::map<std::string, std::string>& filters) {
            manager->remove(storeName, filters);
        }
    };
}

#endif // FEGN_DATA_HPP
