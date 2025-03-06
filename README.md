# Application "Calendar", Author: Byaliauski Yahor

## Assignment

This project falls under the category of interactive applications. The goal is to create an application that the user can control interactively (e.g., using commands via standard input). Do not define parameters directly in the code (not even using constants). Place them in configuration files (one or more) that your program will read.

Your goal is to implement an application for managing calendars and events within them.

Implement the following functionalities:

1. The calendar must display at least a daily, weekly, and monthly overview of events.

2. For events, we want to track at least the following information: event name, date and time, duration, location, participants, tags, and a text note. You can add other interesting attributes (e.g., participation: mandatory, movable, optional, etc.).

3. Events can be one-time or recurring. Allow defining the recurrence frequency at least on a daily basis.

4. The calendar must allow searching for events based on individual attributes, including combinations containing "and" and "or" (e.g., events before 23.01.2022 and in Prague, etc.).

5. Allow exporting and importing events. Events can also be exported from a selection defined by a search.

6. The calendar must not allow collisions. In the case of a collision, it should allow finding the nearest available time slot or moving the event (if possible). Alternatively, you may allow a maximum number of collisions (e.g., 24 collisions for a classroom based on the number of students it can accommodate), but collisions cannot be ignored.

## Specification

The application interface is via the console. The user can enter different commands to control the application. A summary of all commands can be accessed via the /help command:

- /help - summary of all commands
- /get calendar year - display the calendar for this year
- /get calendar [month] - display the calendar for a specific month of this year
- /set event - create an event

> Mandatory event parameters:
> - Name
> - Date
> - Frequency (One-time, Yearly)

> Optional event parameters:
> - Time and duration of the event
> - Location
> - Tags
> - Text note
> - Mandatory/Optional (by default, the event is mandatory)
> - Participants

- /get events - display all events
- /find event - find and display events based on specific parameters
> Entering mandatory parameters may have the following form:
> - Name: Birthday
> - Frequency: (choose between 1 - one-time, 2 - yearly)
> - Date: 23.06.2005
> - Time: 10:30
> - Place: Park | Club
> - Tag: #party | #music

> Logical operator '|' (or) can be used. The user may leave an attribute blank if they do not want to search based on that attribute.
- /set id - set a new attribute for an event
- /del id - delete an event
- /del event all - delete all events
- /time - display the current time
- /date - display the current date
- /clear - clear the terminal
- /exit - exit the application

The application has its own storage where it saves events. The interface uses different colors to improve readability.

## Polymorphism

Polymorphism is used in the "CAttribute" class hierarchy, which has subclasses "CDate", "CTime", "CParticipant", "CPlace", "CTag", "CText", and "CName". Additionally, polymorphism is applied in the "CCalendar" class hierarchy, with subclasses "CCalendarDay", "CCalendarMonth", and "CCalendarYear".

The subclasses of the attribute classes have a shared destructor and methods such as setAttr, which sets a new attribute value, inputAttr, which displays an interactive menu for the respective attribute, and the empty method, which checks if the attribute is empty.

The subclasses of the "CCalendar" class share a common destructor and the printCalendar method, which prints the corresponding calendar type for each subclass. Additionally, the "CCalendarYear" class uses the printCalendar method to display the calendar for each month of the year. The input parameters for each calendar type differ.
