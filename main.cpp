#include <QApplication>
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QMessageBox>
#include <vector>
#include <string>

struct Task {
    std::string name;
    bool completed = false;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Task storage with fake data
    std::vector<Task> tasks = {
        {"Buy groceries", false},
        {"Finish homework", true},
        {"Call mom", false}
    };

    // Main window
    QWidget window;
    window.setWindowTitle("Simple Task Manager");
    window.setMinimumSize(400, 300);

    QStackedWidget *stack = new QStackedWidget();

    // Shared widgets
    QListWidget *taskList = new QListWidget();
    QLineEdit *taskInput = new QLineEdit();
    QLabel *statsLabel = new QLabel();

    // Helper: refresh task list
    auto refreshList = [&]() {
        taskList->clear();
        for (const auto &t : tasks) {
            QString display = QString::fromStdString(t.name);
            display = (t.completed ? "✓ " : "○ ") + display;
            taskList->addItem(display);
        }
    };

    // PAGE 1: Task List
    QWidget *page1 = new QWidget();
    QVBoxLayout *layout1 = new QVBoxLayout(page1);
    layout1->addWidget(new QLabel("<h2>My Tasks</h2>"));
    layout1->addWidget(taskList);

    QPushButton *completeBtn = new QPushButton("Mark Complete");
    QPushButton *toAddPage = new QPushButton("Add Task");
    QPushButton *toStatsPage = new QPushButton("View Stats");

    QHBoxLayout *btnRow = new QHBoxLayout();
    btnRow->addWidget(completeBtn);
    btnRow->addWidget(toAddPage);
    btnRow->addWidget(toStatsPage);
    layout1->addLayout(btnRow);

    // PAGE 2: Add Task
    QWidget *page2 = new QWidget();
    QVBoxLayout *layout2 = new QVBoxLayout(page2);
    layout2->addWidget(new QLabel("<h2>Add New Task</h2>"));
    taskInput->setPlaceholderText("Enter task name...");
    layout2->addWidget(taskInput);

    QPushButton *addBtn = new QPushButton("Add Task");
    QPushButton *backBtn1 = new QPushButton("Back to List");
    layout2->addWidget(addBtn);
    layout2->addWidget(backBtn1);
    layout2->addStretch();

    // PAGE 3: Stats
    QWidget *page3 = new QWidget();
    QVBoxLayout *layout3 = new QVBoxLayout(page3);
    layout3->addWidget(new QLabel("<h2>Task Statistics</h2>"));
    statsLabel->setStyleSheet("font-size: 14px; padding: 10px;");
    layout3->addWidget(statsLabel);

    QPushButton *backBtn2 = new QPushButton("Back to List");
    layout3->addWidget(backBtn2);
    layout3->addStretch();

    // Add pages
    stack->addWidget(page1);
    stack->addWidget(page2);
    stack->addWidget(page3);

    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    mainLayout->addWidget(stack);

    // FUNCTION 1: Add Task
    QObject::connect(addBtn, &QPushButton::clicked, [&]() {
        QString text = taskInput->text().trimmed();
        if (text.isEmpty()) {
            QMessageBox::warning(&window, "Error", "Please enter a task name!");
            return;
        }
        tasks.push_back({text.toStdString(), false});
        taskInput->clear();
        refreshList();
        QMessageBox::information(&window, "Success", "Task added!");
        stack->setCurrentIndex(0);
    });

    // FUNCTION 2: Mark Complete
    QObject::connect(completeBtn, &QPushButton::clicked, [&]() {
        int row = taskList->currentRow();
        if (row < 0 || row >= (int)tasks.size()) {
            QMessageBox::warning(&window, "Error", "Select a task first!");
            return;
        }
        tasks[row].completed = true;
        refreshList();
    });

    // FUNCTION 3: Update Stats
    auto updateStats = [&]() {
        int total = tasks.size();
        int completed = 0;
        for (const auto &t : tasks) if (t.completed) completed++;
        int pending = total - completed;
        int pct = total > 0 ? (completed * 100 / total) : 0;
        statsLabel->setText(QString(
            "Total Tasks: %1\n\nCompleted: %2\n\nPending: %3\n\nCompletion: %4%"
        ).arg(total).arg(completed).arg(pending).arg(pct));
    };

    // Navigation
    QObject::connect(toAddPage, &QPushButton::clicked, [&]() { stack->setCurrentIndex(1); });
    QObject::connect(toStatsPage, &QPushButton::clicked, [&]() { updateStats(); stack->setCurrentIndex(2); });
    QObject::connect(backBtn1, &QPushButton::clicked, [&]() { stack->setCurrentIndex(0); });
    QObject::connect(backBtn2, &QPushButton::clicked, [&]() { stack->setCurrentIndex(0); });

    refreshList();
    window.show();
    return app.exec();
}
