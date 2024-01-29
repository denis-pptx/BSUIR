#include "Test.h"


Test::Test(QUrl url_)
    : passingTime(QPair<bool, int>(false, 1))
    , url(url_)
{


}

void Test::addTask(Task* task) {

    taskList.push_back(task);



}

void Test::removeTask(int i) {

    if (i < 0 || i >= taskList.size())
        throw std::exception();




    taskList.erase(taskList.cbegin() + i);


}


void Test::open() {

    QFile* file = new QFile;
    file->setFileName(url.toString());

    if (file->open(QIODevice::ReadOnly)) {



        // Число заданий
        int32_t N = 0;
        file->read((char*)&N, sizeof(int32_t));

        // Время прохождения
        file->read((char*)&(passingTime.first), sizeof(bool));
        file->read((char*)&(passingTime.second), sizeof(int32_t));

        for (int32_t i = 0; i < N; i++) {

            TaskType taskType;
            file->read((char*)&taskType, sizeof(int32_t));

            addTask(TaskService::objByType(taskType));

            taskList.back()->read(file);

        }

    }
    else
    {
        qDebug() << "BAD OPEN";
    }

    file->close();

    delete file;



}

TestExecute Test::execute()
{
    TestExecute tmp;

    for(auto task : taskList)
    {
       if(task->execute().first)
       {
           tmp.score.first += task->execute().second;
           tmp.tasks.first++;
       }
       tmp.score.second += task->execute().second;
       tmp.tasks.second++;
    }
    return tmp;
}


Task* Test::back() {
    return taskList.back();
}

Task* Test::operator[](int i) {
    return taskList[i];
}

void Test::setPassingTime(bool flag, int duration) {

    if (this->passingTime.second == duration
            && this->passingTime.first == flag)
        return;

    passingTime.first = flag;
    passingTime.second = duration;

}

void Test::setPassingTime(QPair<bool, int32_t> passingTime) {

    if (this->passingTime.second == passingTime.second
            && this->passingTime.first == passingTime.first)
        return;

    this->passingTime = passingTime;

}

QPair<bool, int32_t> Test::getPassingTime() {
    return passingTime;

}

int Test::size() {
    return taskList.size();
}


QUrl Test::getUrl() {
    return url;
}

void Test::setWatchMistakesEnabled(bool flag) {
    for (int i = 0; i < taskList.size(); i++)
        taskList[i]->setWatchMistakesEnabled(flag);
}
