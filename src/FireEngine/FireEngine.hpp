#pragma once
#include <mutex>
#include <set>
#include "Observer.hpp"
#include "PointWGS.hpp"
#include "State.hpp"
class FireEngine
{
    using FireEngineOberver = Observer<FireEngine, State>;

    int id_;
    std::string ownerUnitName_;
    std::shared_ptr<State> state_;
    std::set<FireEngineOberver*> observers_;
    mutable std::mutex mtx_;

public:
    FireEngine() = delete;
    FireEngine(const uint8_t& id, const std::string ownerUnitName);
    uint8_t getId() const { return id_; }
    std::string getOwnerUnitName() const { return ownerUnitName_; }
    bool attach(FireEngineOberver* observer);
    bool detach(FireEngineOberver* observer);
    void notify(std::shared_ptr<State> state);
    void printInfo() const;
    bool isFree() const;
    std::shared_ptr<State> getState() const { return state_; }
    void changeState(std::shared_ptr<State> state);
    void lock() const { std::lock_guard<std::mutex> lock(mtx_); }
};