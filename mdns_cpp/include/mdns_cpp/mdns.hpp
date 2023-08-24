#pragma once

#include <functional>
#include <string>
#include <thread>
#include <vector>
#include <unordered_map>

#include "mdns_cpp/defs.hpp"

struct sockaddr;

namespace mdns_cpp {

struct Query_result {
  Query_result(std::string& service_name, std::string canonical_hostname, std::string& mdnsAddress, uint16_t port) {	  
	  this->service_name = service_name;
    this->mdnsAddress = mdnsAddress;
    this->port = port;
    this->canonical_hostname = canonical_hostname;
  } 

  std::string   service_name;
  std::string   canonical_hostname;
  std::string   mdnsAddress;  // normally x.x.x.x:5353
  std::string   txt;
  uint16_t		  port;
  std::string   ipV4_adress;
  std::string   ipV6_adress;  
};

using QueryResList = std::vector<Query_result>;

class mDNS { 
 public:
  ~mDNS();

  void startService();
  void stopService();
  bool isServiceRunning();

  void setServiceHostname(const std::string &hostname);

  void          setServicePort(std::uint16_t port);
  std::uint16_t getServicePort();

  void          setServiceIP(std::uint32_t ip);
  std::uint32_t getServiceIP();

  std::string   getServiceIPPort(); // IP:Port

  void setServiceName(const std::string &name);
  void setServiceTxtRecord(const std::string &text_record);
  std::vector<std::pair<std::string, uint32_t>> getInterfaces();

  QueryResList executeQuery2(const std::string &service);

  void executeQuery(const std::string &service);
  void executeDiscovery();
  

 private:
  void runMainLoop();
  int openClientSockets(int *sockets, int max_sockets, int port);
  int openServiceSockets(int *sockets, int max_sockets);

  std::string hostname_{"dummy-host"};
  std::string name_{"_http._tcp.local."};
  std::uint16_t port_{42424};
  std::string txt_record_{};

  bool running_{false};

  bool has_ipv4_{false};
  bool has_ipv6_{false};

  uint32_t service_address_ipv4_{0};
  std::vector<std::pair<std::string, uint32_t>> fInterfaces;
  uint8_t service_address_ipv6_[16]{0};

  std::thread worker_thread_;
};

}  // namespace mdns_cpp
