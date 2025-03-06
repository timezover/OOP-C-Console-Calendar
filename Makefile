CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++17

HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
TESTS = $(wildcard tests/*.test.cpp)

TEXT_FILES = events.txt eventexport.txt commands.txt helpfile.txt
TEXT_FILES_DEST = $(addprefix build/, $(TEXT_FILES))

.DEFAULT_GOAL := all

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	./byaliyah

.PHONY: compile
compile: byaliyah $(TEXT_FILES_DEST)

byaliyah: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) $^ -o $@

build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -c -o $@

build/events.txt: assets/events.txt
	mkdir -p $(@D)
	cp $< $@

build/eventexport.txt: assets/eventexport.txt
	mkdir -p $(@D)
	cp $< $@

build/commands.txt: assets/commands.txt
	mkdir -p $(@D)
	cp $< $@

build/helpfile.txt: assets/helpfile.txt
	mkdir -p $(@D)
	cp $< $@

debug/%.test: tests/%.test.cpp $(filter-out build/main.o,$(OBJECTS))
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< $(filter-out build/main.o,$(OBJECTS)) -I src/ -o $@

Doxyfile:
	doxygen -g

.PHONY: doc
doc: Doxyfile $(HEADERS)
	rm -rf doc
	mkdir -p doc
	doxygen Doxyfile
	mv doc/doc/* doc
	rm -rf doc/doc

.PHONY: clean
clean:
	rm -rf byaliyah debug/ build/ 2>/dev/null

.PHONY: test_all
test_all: $(TESTS:tests/%.test.cpp=debug/%.test)
	for TEST in debug/*.test; do ./$$TEST; done
	rm -rf debug

CApplication.o: src/CApplication.cpp src/CApplication.h src/CCommand.h \
 src/CEvent.h src/CText.h src/CAttribute.h src/CTime.h src/CPlace.h \
 src/CDate.h src/CName.h src/CTag.h src/CParticipant.h
CAttribute.o: src/CAttribute.cpp
CCalendar.o: src/CCalendar.cpp
CCalendarDay.o: src/CCalendarDay.cpp src/CCalendarDay.h src/CCalendar.h \
 src/CEvent.h src/CText.h src/CAttribute.h src/CTime.h src/CPlace.h \
 src/CDate.h src/CName.h src/CTag.h src/CParticipant.h src/CInterface.h \
 src/CCommand.h src/CCalendarMonth.h src/CCalendarYear.h
CCalendarMonth.o: src/CCalendarMonth.cpp src/CCalendarMonth.h \
 src/CCalendar.h src/CEvent.h src/CText.h src/CAttribute.h src/CTime.h \
 src/CPlace.h src/CDate.h src/CName.h src/CTag.h src/CParticipant.h
CCalendarYear.o: src/CCalendarYear.cpp src/CCalendarYear.h \
 src/CCalendar.h src/CEvent.h src/CText.h src/CAttribute.h src/CTime.h \
 src/CPlace.h src/CDate.h src/CName.h src/CTag.h src/CParticipant.h \
 src/CCalendarMonth.h
CCommand.o: src/CCommand.cpp src/CCommand.h src/CEvent.h src/CText.h \
 src/CAttribute.h src/CTime.h src/CPlace.h src/CDate.h src/CName.h \
 src/CTag.h src/CParticipant.h src/CInterface.h src/CCalendarMonth.h \
 src/CCalendar.h src/CCalendarYear.h src/CCalendarDay.h src/CSearch.h
CDate.o: src/CDate.cpp src/CDate.h src/CCommand.h
CEvent.o: src/CEvent.cpp src/CEvent.h src/CText.h src/CAttribute.h \
 src/CTime.h src/CPlace.h src/CDate.h src/CName.h src/CTag.h \
 src/CParticipant.h src/CInterface.h src/CCommand.h src/CCalendarMonth.h \
 src/CCalendar.h src/CCalendarYear.h src/CCalendarDay.h
CInterface.o: src/CInterface.cpp src/CInterface.h src/CCommand.h \
 src/CEvent.h src/CText.h src/CAttribute.h src/CTime.h src/CPlace.h \
 src/CDate.h src/CName.h src/CTag.h src/CParticipant.h \
 src/CCalendarMonth.h src/CCalendar.h src/CCalendarYear.h \
 src/CCalendarDay.h
CName.o: src/CName.cpp src/CName.h src/CAttribute.h src/CCommand.h
CParticipant.o: src/CParticipant.cpp src/CParticipant.h src/CAttribute.h
CPlace.o: src/CPlace.cpp src/CPlace.h src/CAttribute.h src/CCommand.h \
 src/CEvent.h src/CText.h src/CTime.h src/CDate.h src/CName.h src/CTag.h \
 src/CParticipant.h
CSearch.o: src/CSearch.cpp src/CSearch.h src/CEvent.h src/CText.h \
 src/CAttribute.h src/CTime.h src/CPlace.h src/CDate.h src/CName.h \
 src/CTag.h src/CParticipant.h
CTag.o: src/CTag.cpp src/CTag.h src/CAttribute.h src/CCommand.h
CText.o: src/CText.cpp src/CText.h src/CAttribute.h src/CCommand.h
CTime.o: src/CTime.cpp src/CTime.h src/CAttribute.h src/CCommand.h src/CEvent.h \
 src/CText.h src/CPlace.h src/CDate.h src/CName.h src/CTag.h \
 src/CParticipant.h
main.o: src/main.cpp src/CApplication.h src/CCommand.h src/CEvent.h \
 src/CText.h src/CAttribute.h src/CTime.h src/CPlace.h src/CDate.h \
 src/CName.h src/CTag.h src/CParticipant.h


debug/CDate.test.o: tests/CDate.test.cpp src/CDate.h
debug/CTime.test.o: tests/CTime.test.cpp src/CTime.cpp src/CTime.h src/CAttribute.h src/CEvent.h \
 src/CText.h src/CPlace.h src/CDate.h src/CName.h src/CTag.h \
 src/CParticipant.h
debug/CTag.test.o: tests/CTag.test.cpp src/CTag.cpp src/CTag.h src/CAttribute.h