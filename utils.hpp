#ifndef PROTOCOL_UTILS_HPP
#define PROTOCOL_UTILS_HPP

#include <google/protobuf/timestamp.pb.h>
#include <chrono>
#include <iostream>
#include <string>

inline std::chrono::time_point<std::chrono::steady_clock> convert_timestamp(
    const ::google::protobuf::Timestamp& timestamp) {
    return std::chrono::time_point<std::chrono::steady_clock>(std::chrono::seconds(timestamp.seconds())
                                                              + std::chrono::nanoseconds(timestamp.nanos()));
}

template <typename T>
std::string team_colour(const T& team) {
    switch (team) {
        case T::BLUE: return "BLUE";
        case T::RED: return "RED";
        default: return "UNKNOWN";
    }
}

template <typename T>
std::string state(const T& state) {
    switch (state) {
        case T::PENALISED: return "PENALISED";
        case T::UNPENALISED: return "UNPENALISED";
        default: return "UNKNOWN";
    }
}

template <typename T>
inline void print_message(const T& msg) {
    std::cout << "Parsed Message:" << std::endl;
    std::cout << "    Sent........: " << convert_timestamp(msg.timestamp()).time_since_epoch().count() << std::endl;
    std::cout << "    Received....: " << convert_timestamp(msg.received()).time_since_epoch().count() << std::endl;
    std::cout << "    Pose........: " << std::endl;
    std::cout << "        Player ID..: " << msg.pose().player_id() << std::endl;
    std::cout << "        Team Colour: " << team_colour(msg.pose().team()) << std::endl;
    std::cout << "        Position...: [" << msg.pose().position().x() << ", " << msg.pose().position().y() << ", "
              << msg.pose().position().z() << "]" << std::endl;
    std::cout << "        Covariance.: " << std::endl;
    std::cout << "            [" << msg.pose().covariance().x().x() << ", " << msg.pose().covariance().y().x() << ", "
              << msg.pose().covariance().z().x() << "]" << std::endl;
    std::cout << "            [" << msg.pose().covariance().x().y() << ", " << msg.pose().covariance().y().y() << ", "
              << msg.pose().covariance().z().y() << "]" << std::endl;
    std::cout << "            [" << msg.pose().covariance().x().z() << ", " << msg.pose().covariance().y().z() << ", "
              << msg.pose().covariance().z().z() << "]" << std::endl;
    std::cout << "    Ball........: " << std::endl;
    std::cout << "        Position...: [" << msg.ball().position().x() << ", " << msg.ball().position().y() << ", "
              << msg.ball().position().z() << "]" << std::endl;
    std::cout << "        Velocity...: [" << msg.ball().velocity().x() << ", " << msg.ball().velocity().y() << ", "
              << msg.ball().velocity().z() << "]" << std::endl;
    std::cout << "        Covariance.: " << std::endl;
    std::cout << "            [" << msg.ball().covariance().x().x() << ", " << msg.ball().covariance().y().x() << ", "
              << msg.ball().covariance().z().x() << "]" << std::endl;
    std::cout << "            [" << msg.ball().covariance().x().y() << ", " << msg.ball().covariance().y().y() << ", "
              << msg.ball().covariance().z().y() << "]" << std::endl;
    std::cout << "            [" << msg.ball().covariance().x().z() << ", " << msg.ball().covariance().y().z() << ", "
              << msg.ball().covariance().z().z() << "]" << std::endl;
    std::cout << "    Walk Command: " << msg.walk_command().x() << ", " << msg.walk_command().y() << ", "
              << msg.walk_command().z() << "]" << std::endl;
    std::cout << "    Target......: " << std::endl;
    std::cout << "        Player ID..: " << msg.target_pose().player_id() << std::endl;
    std::cout << "        Team Colour: " << team_colour(msg.target_pose().team()) << std::endl;
    std::cout << "        Position...: [" << msg.target_pose().position().x() << ", "
              << msg.target_pose().position().y() << ", " << msg.target_pose().position().z() << "]" << std::endl;
    std::cout << "        Covariance.: " << std::endl;
    std::cout << "            [" << msg.target_pose().covariance().x().x() << ", "
              << msg.target_pose().covariance().y().x() << ", " << msg.target_pose().covariance().z().x() << "]"
              << std::endl;
    std::cout << "            [" << msg.target_pose().covariance().x().y() << ", "
              << msg.target_pose().covariance().y().y() << ", " << msg.target_pose().covariance().z().y() << "]"
              << std::endl;
    std::cout << "            [" << msg.target_pose().covariance().x().z() << ", "
              << msg.target_pose().covariance().y().z() << ", " << msg.target_pose().covariance().z().z() << "]"
              << std::endl;
    std::cout << "    Kick Target: [" << msg.kick_target().x() << ", " << msg.kick_target().y() << "]" << std::endl;
    std::cout << "    State......: " << state(msg.state()) << std::endl;

    if (msg.others_size() > 0) {
        std::cout << "    Others......: " << std::endl;
        for (int other = 0; other < msg.others_size(); ++other) {
            std::cout << "        Player ID..: " << msg.others(other).player_id() << std::endl;
            std::cout << "        Team Colour: " << team_colour(msg.others(other).team()) << std::endl;
            std::cout << "        Position...: [" << msg.others(other).position().x() << ", "
                      << msg.others(other).position().y() << ", " << msg.others(other).position().z() << "]"
                      << std::endl;
            std::cout << "        Covariance.: " << std::endl;
            std::cout << "            [" << msg.others(other).covariance().x().x() << ", "
                      << msg.others(other).covariance().y().x() << ", " << msg.others(other).covariance().z().x() << "]"
                      << std::endl;
            std::cout << "            [" << msg.others(other).covariance().x().y() << ", "
                      << msg.others(other).covariance().y().y() << ", " << msg.others(other).covariance().z().y() << "]"
                      << std::endl;
            std::cout << "            [" << msg.others(other).covariance().x().z() << ", "
                      << msg.others(other).covariance().y().z() << ", " << msg.others(other).covariance().z().z() << "]"
                      << std::endl;
        }
    }
}

template <typename T>
inline void parse_message(const std::string& string_msg) {
    // Parse the message using the official protobuf message format
    T msg;

    // Parse the received message, this will ignore any IDs that aren't defined in the official message
    msg.ParseFromString(string_msg);

    // Set the received timestamp
    auto d       = std::chrono::steady_clock::now().time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(d);
    auto nanos   = std::chrono::duration_cast<std::chrono::nanoseconds>(d - seconds);
    msg.mutable_received()->set_seconds(seconds.count());
    msg.mutable_received()->set_nanos(nanos.count());

    print_message<T>(msg);
}

#endif  // PROTOCOL_UTILS_HPP