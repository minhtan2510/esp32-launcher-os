# ESP32-Launcher-OS

A smartwatch-inspired application platform for ESP32 devices.

LauncherOS is a personal learning project focused on modern C++ development, embedded software architecture, and application-oriented firmware design.

Instead of building a single-purpose ESP32 application, LauncherOS aims to provide a reusable platform consisting of:

* Application Launcher
* Event-driven Architecture
* Widget-based UI Framework
* Service Layer
* Application Framework
* Hardware Abstraction Layer

The project is designed for small displays and button-based navigation, inspired by smartwatch operating systems such as watchOS, Wear OS, and PebbleOS.

---

## Goals

### Technical Goals

* Learn modern C++ in embedded systems
* Build a modular firmware architecture
* Understand FreeRTOS concepts
* Practice event-driven programming
* Implement a lightweight UI framework
* Develop reusable application components

### Functional Goals

* Application Launcher
* Clock Application
* Weather Application
* IoT Dashboard
* TOTP Authenticator
* Music Controller
* Mini Games
* System Settings

---

## Hardware

Current target hardware:

| Component    | Description           |
| ------------ | --------------------- |
| MCU          | ESP32                 |
| Display      | 1.77" LCD 168x128 RGB |
| Input        | 3 Push Buttons        |
| Connectivity | WiFi / Bluetooth      |
| Framework    | ESP-IDF               |
| IDE          | VSCode(PlatformIO)    |

---

## Architecture

```text
+-----------------------+
|       LauncherOS         |
+-----------------------+

        Core
          |
          v

+-----------------------+
|    Event System       |
+-----------------------+

          |
          v

+-----------------------+
|      Launcher         |
+-----------------------+

          |
          v

+-----------------------+
|        Apps           |
+-----------------------+

          |
          v

+-----------------------+
|      Services         |
+-----------------------+

          |
          v

+-----------------------+
|       Drivers         |
+-----------------------+
```

---

## Project Structure

```text
orbit-os/
│
├── docs/
│
├── hardware/
│
├── components/
│   │
│   ├── core/
│   │
│   ├── drivers/
│   │
│   ├── ui/
│   │
│   ├── services/
│   │
│   └── apps/
│
├── main/
│   └── main.cpp
│
├── test/
│
├── platformio.ini
│
├── README.md
│
└── ROADMAP.md
```

---

## Core Components

### Core

Responsible for:

* System initialization
* State management
* Application lifecycle
* Event dispatching

Examples:

```text
AppManager
StateMachine
EventBus
System
```

---

### Drivers

Hardware abstraction layer.

Examples:

```text
DisplayDriver
ButtonDriver
WifiDriver
BatteryDriver
```

Applications should never access GPIO directly.

---

### Services

Reusable system services.

Examples:

```text
TimeService
WeatherService
NetworkService
BatteryService
MQTTService
```

Applications consume services instead of talking directly to hardware or external APIs.

---

### UI

Lightweight widget framework.

Examples:

```text
Widget
Label
Icon
ProgressBar
ListView
Screen
```

---

### Apps

Independent applications.

Examples:

```text
ClockApp
WeatherApp
DashboardApp
TOTPApp
GameApp
SettingsApp
```

Each app follows a common lifecycle.

```cpp
enter()
update()
draw()
exit()
```

---

## Input System

LauncherOS uses a polling-based input system.

```text
Buttons
    ↓
Button Manager
    ↓
Event Queue
    ↓
Launcher / Apps
```

Supported events:

```text
Short Press
Long Press
Repeat
Double Click
```

---

## Launcher Design

Navigation is inspired by smartwatch interfaces.

```text
        [ICON]

       CLOCK

     ● ○ ○ ○ ○
```

Controls:

```text
BTN1 -> Previous App
BTN2 -> Open App
BTN3 -> Next App
```

Inside applications:

```text
BTN2 Long Press -> Return Home
```

---
## Coding Guidelines

### Naming Convention

Classes:

```cpp
ButtonManager
WeatherService
ClockApp
```

Methods:

```cpp
update()
draw()
handleEvent()
```

Variables:

```cpp
currentApp
buttonState
eventQueue
```

Constants:

```cpp
MAX_APPS
LONG_PRESS_TIME_MS
```

---

## Git Workflow

Feature Branches:

```text
feature/display-driver
feature/button-manager
feature/event-bus
feature/launcher
feature/weather-app
```

Commit Format:

```text
feat(button): add long press detection

feat(core): implement event queue

feat(launcher): add application registry

fix(display): correct icon rendering
```

---

## Long-Term Vision

LauncherOS is not intended to become a full operating system.

The goal is to serve as a practical learning platform for:

* Modern C++
* Embedded Architecture
* FreeRTOS
* GUI Systems
* Event-Driven Design
* Software Engineering Practices

while building a fully functional smartwatch-style application ecosystem on ESP32.

---

## License

MIT License
