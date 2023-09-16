// #include <librdkafka/rdkafkacpp.h>
// #include <cpprest/http_listener.h>
// #include <cpprest/json.h>
// #include <thread>

// using namespace web;
// using namespace http;
// using namespace http::experimental::listener;
// // Global Kafka producer and consumer objects
// RdKafka::Producer* producer = nullptr;
// RdKafka::Consumer* consumer = nullptr;
// void produceToKafka(const std::string& message) {
//     if (!producer) {
//         return;
//     }
//     std::string topic = "your-topic";
//     RdKafka::Topic* rdTopic;  // = RdKafka::Topic::create(producer, topic, nullptr, RdKafka::Topic::PARTITION_UA)
//     if (!rdTopic) {
//         return;
//     }
//     RdKafka::ErrorCode resp = producer->produce(rdTopic, RdKafka::Topic::PARTITION_UA,
//         RdKafka::Producer::RK_MSG_COPY, const_cast<char*>(message.c_str()), message.size(),
//         nullptr, nullptr);
//     if (resp != RdKafka::ERR_NO_ERROR) {
//     }
//     producer->poll(0);
//     delete rdTopic;
// }
// void consumeFromKafka() {
//     if (!consumer) {
//         return;
//     }
//     std::vector<std::string> topics = { "your-topic" };
//     // RdKafka::ErrorCode resp = consumer->subscribe(topics);
//     // if (resp != RdKafka::ERR_NO_ERROR) {
//     //     return;
//     // }
//     while (true) {
//         RdKafka::Message* message = consumer->consume(0, 1000);
//         if (message->err()) {
//         } else {
//         }
//         delete message;
//     }
// }
// void startRestApi() {
//     http_listener listener("http://localhost:8080");
//     listener.support(methods::POST, [](http_request request) {
//         // Handle POST requests here
//         json::value response;
//         response[U("message")] = json::value::string(U("Message received!"));
//         request.reply(status_codes::OK, response);
//     });
//     listener.support(methods::GET, [](http_request request) {
//         // Handle GET requests here
//         json::value response;
//         response[U("data")] = json::value::string(U("Sample JSON data"));
//         request.reply(status_codes::OK, response);
//     });
//     try {
//         listener.open().wait();
//         while (true) {
//             std::this_thread::sleep_for(std::chrono::milliseconds(100));
//         }
//     } catch (const std::exception& e) {
//     }
// }
// int main() {
//     std::string errstr;
//     RdKafka::Conf* producerConf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
//     producerConf->set("bootstrap.servers", "localhost:9092", errstr);
//     producer = RdKafka::Producer::create(producerConf, errstr);
//     RdKafka::Conf* consumerConf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
//     consumerConf->set("bootstrap.servers", "localhost:9092", errstr);
//     consumerConf->set("group.id", "your-consumer-group", errstr);
//     consumer = RdKafka::Consumer::create(consumerConf, errstr);
//     std::thread kafkaThread(consumeFromKafka);
//     std::thread restApiThread(startRestApi);
//     produceToKafka("Hello, Kafka!");
//     kafkaThread.join();
//     restApiThread.join();
//     delete consumer;
//     delete producer;
//     return 0;
// }