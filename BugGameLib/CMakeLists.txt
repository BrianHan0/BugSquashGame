project(BugGameLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h GameView.cpp GameView.h Game.cpp Game.h Bug.cpp Bug.h Scoreboard.cpp
        Scoreboard.h BugFeature.cpp BugFeature.h ids.h BugGarbage.cpp BugGarbage.h BugNull.cpp BugNull.h
        BugRedundancy.cpp BugRedundancy.h FatBug.cpp FatBug.h Laptop.cpp Laptop.h Item.cpp Item.h ItemVisitor.cpp ItemVisitor.h DeleteCloseBugs.cpp DeleteCloseBugs.h Message.cpp Message.h FatGarbageBug.cpp FatGarbageBug.h)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)