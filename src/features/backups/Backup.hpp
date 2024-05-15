#pragma once

#include <Geode/binding/GJGameLevel.hpp>

using namespace geode::prelude;

class Backup final {
public:
    using Clock = std::chrono::system_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    using TimeUnit = std::chrono::minutes;

private:
    ghc::filesystem::path m_directory;
    Ref<GJGameLevel> m_level;
    Ref<GJGameLevel> m_forLevel;
    TimePoint m_createTime;
    bool m_automated;

public:
    static Result<std::shared_ptr<Backup>> load(ghc::filesystem::path const& dir, GJGameLevel* forLevel);
    static std::vector<std::shared_ptr<Backup>> load(GJGameLevel* level);
    static Result<> create(GJGameLevel* level, bool automated);
    static Result<> cleanAutomated(GJGameLevel* level);

    GJGameLevel* getLevel() const;
    GJGameLevel* getOriginalLevel() const;
    TimePoint getCreateTime() const;
    bool isAutomated() const;

    Result<> restoreThis();
    Result<> deleteThis();
    Result<> preserveAutomated();
};
using BackupPtr = std::shared_ptr<Backup>;