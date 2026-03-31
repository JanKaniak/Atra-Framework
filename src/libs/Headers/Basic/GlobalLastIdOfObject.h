#include <cstdint>

class GlobalLastIdOfObject {
    private:
    static GlobalLastIdOfObject* instance_;
    uint64_t lastId_;
    GlobalLastIdOfObject() {
        lastId_ = 0;
    }

    public:
    static GlobalLastIdOfObject* getInstance();
    uint64_t getNewId();
    void resetIdCounter() { lastId_ = 0;}

};

