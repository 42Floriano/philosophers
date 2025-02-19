# 🧠 Philosophers - 42 Project

Philosophers is a **42 School** project designed to introduce **multithreading and concurrency** through the classic **Dining Philosophers Problem**. The project requires implementing a simulation where multiple philosophers share limited resources (forks) without causing deadlocks or starvation.

---

## 📌 What is the Dining Philosophers Problem?

The **Dining Philosophers Problem** is a classic synchronization problem in computer science that illustrates the challenges of **avoiding deadlocks** and **managing shared resources** in concurrent programming. It involves:

- **N philosophers** sitting around a circular table.
- **Each philosopher** has a fork on their left and right.
- A philosopher **must acquire both forks** to eat.
- Philosophers spend their time **thinking, eating, or sleeping**.
- If a philosopher doesn’t eat within a specific time, they **die of starvation**.

The challenge is ensuring that all philosophers get a chance to eat **without conflicts**.

---

## 📁 Repository Structure

```
├── philo/             # Source code for the main program
│   ├── includes/      # Header files
│   ├── srcs/          # Source code files
│   ├── Makefile       # Compilation rules
│   └── README.md      # Project documentation
└── en.subject.pdf     # Project subject file
```

---

## 🚀 Getting Started

### 🔧 Dependencies
This project requires a **POSIX-compliant** system and supports **pthreads**.

For **Debian/Ubuntu**:
```sh
sudo apt-get install build-essential
```

For **MacOS**:
```sh
brew install make
```

---

## 🏗️ Installation

Clone the repository and compile the project using Make:

```sh
git clone https://github.com/42Floriano/philosophers.git
cd philosophers/philo
make
```

This will generate the `philo` executable.

---

## 🎮 How to Run

Run the program with the following arguments:
```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:
```sh
./philo 5 800 200 200
```

### 🕹️ Parameters
- **number_of_philosophers** → Total number of philosophers (and forks).
- **time_to_die** → Time (ms) before a philosopher dies if they don't eat.
- **time_to_eat** → Time (ms) taken to eat.
- **time_to_sleep** → Time (ms) spent sleeping.
- **number_of_times_each_philosopher_must_eat** _(optional)_ → If specified, the simulation ends when all philosophers have eaten at least this many times.

---

## 🔧 Features Implemented
✅ **Thread-based Simulation** → Each philosopher runs as a separate thread.
✅ **Mutex-protected Forks** → Prevents data races.
✅ **Logging System** → Tracks philosopher actions.
✅ **Handles Starvation Prevention** → Ensures philosophers don’t die prematurely.
❌ **Bonus features not implemented** (Process-based simulation, semaphores).

---

## 📌 Credits
- **42Floriano** ([@42Floriano](https://github.com/42Floriano))

---

## 🏆 Acknowledgments
This project was built as part of **42 School**, providing an introduction to **multithreading, mutexes, and concurrency control**.

---

🔗 [GitHub Repository](https://github.com/42Floriano/philosophers)

