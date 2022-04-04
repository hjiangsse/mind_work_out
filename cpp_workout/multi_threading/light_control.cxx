#include <iostream>
#include <cstdint>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

struct Color {
    int r;
    int g;
    int b;
};

struct Message {
    enum class Id {
	SET_STATE = 0,
	SET_INTENSITY,
	SET_COLOR,
	TERMINATE
    };

    union Params {
	Color rgb;
	uint8_t intensity;
	bool state;
    };

    Id id;
    Params params;
};

std::condition_variable cv;
std::mutex m;
std::queue<Message> msg_queue;

void SetState(const bool state) {
    std::cout << "SetState " << state << "\n";
}

void SetIntensity(const uint8_t intensity) {
    std::cout << "SetIntensity " << (unsigned int) intensity << "\n";
}

void SetColor(const Color color) {
    std::cout << "SetColor " << color.r << ", " << color.g << ", " << color.b << "\n";
}

Message GetMessage() {
    Message message;
    std::unique_lock<std::mutex> lock(m);
    
    cv.wait(lock, [](){return not msg_queue.empty();});
    message = msg_queue.front();
    msg_queue.pop();

    return message;
}

void PutMessage(const Message& message) {
    std::lock_guard<std::mutex> lk(m);
    msg_queue.push(message);
    cv.notify_one();
}

void controller()
{
    Color white = {255, 255, 255};
    uint8_t intensity = 255;

    PutMessage(Message{Message::Id::SET_STATE, true});      // switch on
    PutMessage(Message{Message::Id::SET_INTENSITY, intensity});   // set the highest intensity
    PutMessage(Message{Message::Id::SET_COLOR, white});     // set color to white
    PutMessage(Message{Message::Id::SET_STATE, false});     // switch off
    PutMessage(Message{Message::Id::TERMINATE});
}

void handler()
{
    while (true) {
        const Message msg = GetMessage();
        switch (msg.id) {
            case Message::Id::SET_STATE:
                SetState(msg.params.state);
                break;
            case Message::Id::SET_INTENSITY:
                SetIntensity(msg.params.intensity);
                break;
            case Message::Id::SET_COLOR:
                SetColor(msg.params.rgb);
                break;
            default:
                break;
        }
    }
}

int main() {
    std::thread c(handler);
    std::thread p(controller);
    
    c.join();
    p.join();

    return 0;
}
