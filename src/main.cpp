#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mqtt/async_client.h>

const std::string SERVER_ADDRESS("tcp://test.mosquitto.org:1883");
const std::string CLIENT_ID("sdv_edge_node_01");
const std::string TOPIC("vehicle/telemetry/v1");

int main() {
    mqtt::async_client cli(SERVER_ADDRESS, CLIENT_ID);
    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);

    try {
        std::cout << "Connecting to MQTT broker at " << SERVER_ADDRESS << "..." << std::flush;
        cli.connect(connOpts)->wait();
        std::cout << " OK.\n";

        for (int i = 0; i < 5; ++i) {
            std::string payload = "{\"speed_kmh\": " + std::to_string(45 + (i * 2)) + ", \"battery_soc\": " + std::to_string(82 - i) + "}";
            std::cout << "Publishing: " << payload << "\n";
            mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC, payload);
            pubmsg->set_qos(1);
            cli.publish(pubmsg)->wait();
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        cli.disconnect()->wait();
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "\nMQTT Error: " << exc.what() << "\n";
        return 1;
    }
    return 0;
}
