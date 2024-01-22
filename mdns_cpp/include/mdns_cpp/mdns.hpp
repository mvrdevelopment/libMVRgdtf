#pragma once

#include <functional>
#include <string>
#include <thread>
#include <vector>
#include <set>
#include <unordered_map>

#include "mdns_cpp/defs.hpp"

struct sockaddr;

namespace mdns_cpp {

struct Query_result {
  Query_result(): port(0){}

  Query_result(std::string canonical_hostname, std::string& mdnsAddress) {	  
    this->canonical_hostname = canonical_hostname;
    this->mdnsAddress = mdnsAddress;
  } 

  std::string   service_name;
  std::string   canonical_hostname;
  std::string   mdnsAddress;
  std::string   txt;
  uint16_t		  port;
  std::set<std::string>   ipV4_address;
  std::set<std::string>   ipV6_address;  
};

template<typename T>
struct unsorted_query_part_t {
  std::string addr;
  std::string canonicalName;
  T data;

  unsorted_query_part_t() = default;
  unsorted_query_part_t(const std::string& addr, const std::string& canonicalName, const T& data): addr(addr), canonicalName(canonicalName), data(data) {};

  bool operator==(const unsorted_query_part_t<T>& o) const{return addr == o.addr && canonicalName == o.canonicalName && data == o.data;};
};

struct srv_record_t
{
  srv_record_t(uint16_t port, std::string name) : port(port), name(name) {};
  srv_record_t(){};

	uint16_t port;
	std::string name;
  bool operator==(const srv_record_t& o) const {return port == o.port && name == o.name;};
};
struct unsorted_query_t {
  std::vector<unsorted_query_part_t<srv_record_t>> srvRecords;
  std::vector<unsorted_query_part_t<std::string>> txtRecords;
  std::vector<unsorted_query_part_t<std::string>> aRecords;
  std::vector<unsorted_query_part_t<std::string>> aaaaRecords;
  std::vector<unsorted_query_part_t<std::string>> ptrRecords;
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
