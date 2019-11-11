#include <google/protobuf/timestamp.pb.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>

#include "robocup.pb.h"

void parse_message(const std::string& msg);
std::string team_colour(const robocup::humanoid::Team& team);
std::string state(const robocup::humanoid::State& state);
std::chrono::time_point<std::chrono::steady_clock> convert_timestamp(const ::google::protobuf::Timestamp& timestamp);

int main(void) {
    // Create a new message which contains extensions
    robocup::humanoid::MessageExtension msg;

    // Set the transmission timestamp
    auto d       = std::chrono::steady_clock::now().time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(d);
    auto nanos   = std::chrono::duration_cast<std::chrono::nanoseconds>(d - seconds);
    msg.mutable_timestamp()->set_seconds(seconds.count());
    msg.mutable_timestamp()->set_nanos(nanos.count());

    // Set player details
    msg.mutable_pose()->set_player_id(3);
    msg.mutable_pose()->set_team(robocup::humanoid::Team::BLUE);
    msg.mutable_pose()->mutable_position()->set_x(1.0f);
    msg.mutable_pose()->mutable_position()->set_y(3.0f);
    msg.mutable_pose()->mutable_position()->set_z(M_PI / 3);
    msg.mutable_pose()->mutable_covariance()->mutable_x()->set_x(1.0f);
    msg.mutable_pose()->mutable_covariance()->mutable_x()->set_y(0.0f);
    msg.mutable_pose()->mutable_covariance()->mutable_x()->set_z(0.0f);
    msg.mutable_pose()->mutable_covariance()->mutable_y()->set_x(0.0f);
    msg.mutable_pose()->mutable_covariance()->mutable_y()->set_y(1.0f);
    msg.mutable_pose()->mutable_covariance()->mutable_y()->set_z(0.0f);
    msg.mutable_pose()->mutable_covariance()->mutable_z()->set_x(0.0f);
    msg.mutable_pose()->mutable_covariance()->mutable_z()->set_y(0.0f);
    msg.mutable_pose()->mutable_covariance()->mutable_z()->set_z(1.0f);

    // Set ball details
    msg.mutable_ball()->mutable_position()->set_x(2.0f);
    msg.mutable_ball()->mutable_position()->set_y(3.0f);
    msg.mutable_ball()->mutable_position()->set_z(1.0f);
    msg.mutable_ball()->mutable_velocity()->set_x(0.5f);
    msg.mutable_ball()->mutable_velocity()->set_y(0.5f);
    msg.mutable_ball()->mutable_velocity()->set_z(-0.5f);
    msg.mutable_ball()->mutable_covariance()->mutable_x()->set_x(1.0f);
    msg.mutable_ball()->mutable_covariance()->mutable_x()->set_y(0.0f);
    msg.mutable_ball()->mutable_covariance()->mutable_x()->set_z(0.0f);
    msg.mutable_ball()->mutable_covariance()->mutable_y()->set_x(0.0f);
    msg.mutable_ball()->mutable_covariance()->mutable_y()->set_y(1.0f);
    msg.mutable_ball()->mutable_covariance()->mutable_y()->set_z(0.0f);
    msg.mutable_ball()->mutable_covariance()->mutable_z()->set_x(0.0f);
    msg.mutable_ball()->mutable_covariance()->mutable_z()->set_y(0.0f);
    msg.mutable_ball()->mutable_covariance()->mutable_z()->set_z(1.0f);

    // Set walk command
    msg.mutable_walk_command()->set_x(0.15f);
    msg.mutable_walk_command()->set_y(0.15f);
    msg.mutable_walk_command()->set_z(-0.05f);

    // Set target pose
    msg.mutable_target_pose()->set_player_id(3);
    msg.mutable_target_pose()->set_team(robocup::humanoid::Team::BLUE);
    msg.mutable_target_pose()->mutable_position()->set_x(2.0f);
    msg.mutable_target_pose()->mutable_position()->set_y(3.0f);
    msg.mutable_target_pose()->mutable_position()->set_z(-M_PI / 3);

    // Set kick target
    msg.mutable_kick_target()->set_x(4.5f);
    msg.mutable_kick_target()->set_y(0.0f);

    // Set state
    msg.set_state(robocup::humanoid::State::UNPENALISED);

    // Set some others details
    robocup::humanoid::Robot* other = msg.add_others();
    other->set_player_id(2);
    other->set_team(robocup::humanoid::Team::BLUE);
    other->mutable_position()->set_x(1.0f);
    other->mutable_position()->set_y(-3.0f);
    other->mutable_position()->set_z(M_PI / 6);
    other->mutable_covariance()->mutable_x()->set_x(1.0f);
    other->mutable_covariance()->mutable_x()->set_y(0.0f);
    other->mutable_covariance()->mutable_x()->set_z(0.0f);
    other->mutable_covariance()->mutable_y()->set_x(0.0f);
    other->mutable_covariance()->mutable_y()->set_y(1.0f);
    other->mutable_covariance()->mutable_y()->set_z(0.0f);
    other->mutable_covariance()->mutable_z()->set_x(0.0f);
    other->mutable_covariance()->mutable_z()->set_y(0.0f);
    other->mutable_covariance()->mutable_z()->set_z(1.0f);

    other = msg.add_others();
    other->set_player_id(1);
    other->set_team(robocup::humanoid::Team::RED);
    other->mutable_position()->set_x(4.5f);
    other->mutable_position()->set_y(0.0f);
    other->mutable_position()->set_z(M_PI);
    other->mutable_covariance()->mutable_x()->set_x(1.0f);
    other->mutable_covariance()->mutable_x()->set_y(0.0f);
    other->mutable_covariance()->mutable_x()->set_z(0.0f);
    other->mutable_covariance()->mutable_y()->set_x(0.0f);
    other->mutable_covariance()->mutable_y()->set_y(1.0f);
    other->mutable_covariance()->mutable_y()->set_z(0.0f);
    other->mutable_covariance()->mutable_z()->set_x(0.0f);
    other->mutable_covariance()->mutable_z()->set_y(0.0f);
    other->mutable_covariance()->mutable_z()->set_z(1.0f);

    other = msg.add_others();
    other->set_player_id(0);
    other->set_team(robocup::humanoid::Team::UNKNOWN_TEAM);
    other->mutable_position()->set_x(4.0f);
    other->mutable_position()->set_y(0.0f);
    other->mutable_position()->set_z(M_PI);
    other->mutable_covariance()->mutable_x()->set_x(1.0f);
    other->mutable_covariance()->mutable_x()->set_y(0.0f);
    other->mutable_covariance()->mutable_x()->set_z(0.0f);
    other->mutable_covariance()->mutable_y()->set_x(0.0f);
    other->mutable_covariance()->mutable_y()->set_y(1.0f);
    other->mutable_covariance()->mutable_y()->set_z(0.0f);
    other->mutable_covariance()->mutable_z()->set_x(0.0f);
    other->mutable_covariance()->mutable_z()->set_y(0.0f);
    other->mutable_covariance()->mutable_z()->set_z(1.0f);

    // ******************************
    // * Official message ends here *
    // ******************************

    // Set max walking speed (an extension value)
    msg.set_max_walking_speed(0.25f);

    // Serialise the extended message in preparation for network transfer
    std::string string_msg = msg.SerializeAsString();

    // "Send" the message over the network and decode it
    parse_message(string_msg);

    return 0;
}

void parse_message(const std::string& string_msg) {
    // Parse the message using the official protobuf message format
    robocup::humanoid::Message msg;

    // Parse the received message, this will ignore any IDs that aren't defined in the official message
    msg.ParseFromString(string_msg);

    // Set the received timestamp
    auto d       = std::chrono::steady_clock::now().time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(d);
    auto nanos   = std::chrono::duration_cast<std::chrono::nanoseconds>(d - seconds);
    msg.mutable_received()->set_seconds(seconds.count());
    msg.mutable_received()->set_nanos(nanos.count());

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

std::string team_colour(const robocup::humanoid::Team& team) {
    switch (team) {
        case robocup::humanoid::Team::BLUE: return "BLUE";
        case robocup::humanoid::Team::RED: return "RED";
        default: return "UNKNOWN";
    }
}

std::string state(const robocup::humanoid::State& state) {
    switch (state) {
        case robocup::humanoid::State::PENALISED: return "PENALISED";
        case robocup::humanoid::State::UNPENALISED: return "UNPENALISED";
        default: return "UNKNOWN";
    }
}

std::chrono::time_point<std::chrono::steady_clock> convert_timestamp(const ::google::protobuf::Timestamp& timestamp) {
    return std::chrono::time_point<std::chrono::steady_clock>(std::chrono::seconds(timestamp.seconds())
                                                              + std::chrono::nanoseconds(timestamp.nanos()));
}