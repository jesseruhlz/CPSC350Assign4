#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <algorithm>
#include "Registrar.h"
using namespace std;

Registrar::Registrar(){
  lineType = 1;
  entryTime = 0;
  StudentTimeAtWindow = 0;
  studAtTime = 0;

  medianCount = 0;
  idleCount = 0;

  totalStuds = 0;
  totalWindows = 0;

  messageString = "minutes";
  showFile = true;
}

Registrar::~Registrar(){
  delete [] windowArray;
  delete [] medianArr;
  delete [] idleArr;
}

bool Registrar::readFile(string f){
  //cout << "ReadFile Function" << endl;
  ifstream infile;
  infile.open(f.c_str());
  string line;
  int lineNum = 1;

  if(infile.is_open()){
    //cout << "File is open" << endl;
    try{
      getline(infile, line);
      totalWindows = stoi(line);
      cout << "Total Open Windows: " << totalWindows << endl;
      //create the windows
      windowArray = new Student*[totalWindows];
      //make windows empty
      for (int i = 0; i < totalWindows; ++i){
        Student* stud = new Student();
        windowArray[i] = stud;
        //cout << "amount of empty windows" << endl;
        //cout << windowArray[i] << endl;
      }
      lineNum++;
    }
    catch (exception e){
      cout << "ERROR AT LINE " << lineNum << endl;
      showFile = false;
      return false;
    }

    while (getline(infile, line)){
      switch (lineType)
      {
        //second line is clock
        case (1):
        {
          //cout << "case 1" << endl;
          try
          {
            entryTime = stoi(line);
            //cout << "Entry Time in case 1: " << endl;
            //cout << entryTime << endl;
            lineType++;
            lineNum++;
          }
          catch (exception e)
          {
            showFile = false;
            return false;
          }
          break;
        }
        //amount of students at time
        case (2):
        {
          //cout << "case 2" << endl;
          try
          {
            if (line != "")
            {
              //num of students
              studAtTime = stoi(line);
              //cout << "number of students at the time" << endl;
              for (int i = 0; i < studAtTime; ++i)
              {
                //individual students
                getline(infile, line);
                lineNum++;
                try
                {
                  //cout << "How much time the students needs at the window" << endl;
                  StudentTimeAtWindow = stoi(line);
                  //cout << StudentTimeAtWindow << endl;
                }
                catch (exception e)
                {
                  showFile = false;
                  return false;
                }
                totalStuds++;
                Student* stud = new Student(StudentTimeAtWindow, entryTime);
                studentQueue.enqueue(stud);
                //studentQueue.printQueue();
              }
              lineType = 1;
            }
          }
          catch (exception e)
          {
            showFile = false;
            return false;
          }
          break;
        }
        default:break;
      }
    }
  }
  else
  {
    return false;
  }
  return true;
}

bool Registrar::incrementTime(int iT)
{
  //cout << "IncrementTime Function" << endl;
  for (int i = 0; i < totalWindows; ++i)
  {
    if (windowArray[i]->timeAtWindow > 0){
      //decrease window time if student there
      windowArray[i]->timeAtWindow--;
    }
    else {
      //increase window idle time if no student there
      windowArray[i]->idle++;
    }
  }
  if (!studentQueue.isEmpty())
  {
    //time in queu of people in queue
    ListNode<Student*> *curr = studentQueue.front;
    while (curr != NULL)
    {
      if (curr->data->entry < iT)
        curr->data->timeInQueue += 1;
      curr = curr->next;
      //cout << "Time in queu of all people in line" << endl;
      //cout << curr << endl;
    }
  }
  return true;
}

double Registrar::meanWait()
{
  //cout << "MeanWait Function" << endl;
  ListNode<int> *curr = waitTime.front;
  double avgWait = 0;
  int sum = 0;
  int counter = 0;
  while (curr != NULL)
  {
    sum += curr->data;
    //cout << "sum for mean wait is " << sum << endl;
    //cout << curr->data << endl;
    if (curr->data != 0)
      counter++;
    curr = curr->next;
    //cout << "the current node is " << curr << endl;

  }
  if (counter == 0){
    minuteMessage(0);
    return 0;
  }
  //cout << "sum value " << sum << '/' << " counter value." << counter << endl;
  avgWait = double(sum) / double(counter);
  //minuteMessage(avgWait);
  return avgWait;
}

double Registrar::medianWait()
{
  //cout << "MedianWait Function" << endl;
  ListNode<int> *curr = waitTime.front;
  int medianIndex = (waitTime.getSize() + 1) / 2;
  //cout << waitTime.getSize();
  //cout << "medianIndex " << medianIndex << endl;
  double u;
  double medWait = 0;
  medianCount = 0;
  while (curr != NULL)
  {
    curr = curr->next;
    //cout << "curr for medianWait list/array " << curr << endl;
    medianCount++;
    if (medianCount == medianIndex){
      u = curr->data;
      //cout << curr->data << endl;
    }
    //return u;
  }

  if (medianCount == 0){
    minuteMessage(0);
    return 0;
  }
  else{
    //int newCount = medianCount / 2;
    medianArr = new int[medianCount];
    curr = waitTime.front;
    for (int i = 0; i < medianCount; ++i)
    {
      medianArr[i] = curr->data;
      curr = curr->next;
      //cout << "medianArr[i] is " << endl;
      //cout << medianArr[i] << endl;
    }
    sort(medianArr,medianArr + medianCount);

    if (medianCount % 2 == 1)
    {
      double d = 0;
      int t = 0;
      t = (medianCount/2) + 1;
      d = medianArr[t];
      minuteMessage(d);
      //return d;
    }
    else{
      double d = 0;
      int t1 = 0;
      int t2 = 0;
      t1 = medianCount / 2;
      t2 = (medianCount / 2) + 1;
      if (medianArr[t2] == 0){
        minuteMessage(0);
        return 0;
      }
      cout << t1 << '/' << t2 << endl;
      d = double(medianArr[t1]) / double(medianArr[t2]);
      minuteMessage(d);
      //return d;
    }
    return u;
  }
}

int Registrar::longestWait()
{
  //cout << "LongestWait Function" << endl;
  if (medianCount != 0){
    //minuteMessage(medianArr[medianCount - 1]);
    return medianArr[medianCount - 1];
  }
  else{
    minuteMessage(0);
    return 0;
  }
}

int Registrar::numStudOverTen(){
  //cout << "NnumberOfStudentsOverTen Function" << endl;
  if (medianCount != 0){
    int g = 0;
    for (int i = 0; i < medianCount; ++i){
      if (medianArr[i] >= 10){
        ++g;
      }
    }
    //minuteMessage(g);
    return g;
  }
  else{
    //minuteMessage(0);
    return 0;
  }
}

int Registrar::meanIdle()
{
  //cout << "MeanIdle Function" << endl;
  ListNode<int> *curr = idleTime.front;
  int avgIdle = 0;
  int sum = 0;
  int counter = 0;
  int sumOfEntryTime = 0;
  /*
  while (curr != NULL){
    for (int i = 0; i < totalWindows; ++i){
      sum += curr->data;
      cout << "sum for elements in idle list " << sum << endl;
      curr = curr->next;
      //cout << "curr for idle list " << curr << endl;
      counter++;
    }
  }
  */
  for (int i = 0; i < totalWindows; ++i){
    sum += curr->data;
    //cout << "sum for elements in idle list " << sum << endl;
    curr = curr->next;
    //cout << "curr for idle list " << curr << endl;
    counter++;
  }
  sumOfEntryTime = (entryTime * totalWindows) / totalWindows;
  //avgIdle = sum / totalWindows;
  return sumOfEntryTime;
}

int Registrar::longestIdle(){
  //cout << "LongestIdle Function" << endl;
  int longestWindowIdleTime = 0;
  ListNode<int> *curr = idleTime.front;
  idleCount = 0;
  while (curr != NULL){
    curr = curr->next;
    idleCount++;
  }
  idleArr = new int[totalWindows];
  curr = idleTime.front;
  for (int i = 0; i < totalWindows; ++i){
    idleArr[i] = curr->data;
    //cout << "idle array elements are " << idleArr[i] << endl;
    curr = curr->next;
    //cout << idleArr[i] << endl;
  }
  sort(idleArr, idleArr + totalWindows);
  longestWindowIdleTime = entryTime;
  //return (idleArr[totalWindows - 1]);
  return longestWindowIdleTime;
}

int Registrar::numIdleOverFive(){
  int g = 0;
  for (int i = 0; i < totalWindows; ++i){
    //cout << "idleArr elements: " << endl;
    //cout << idleArr [i] << endl;
    if (idleArr[i] >= 5){
      ++g;
    }
  }
  //minuteMessage(g);
  return g;
}


string Registrar::getMinuteMess()
{
  return messageString;
}

void Registrar::minuteMessage(int m)
{
  if (m != 1)
    messageString = " minutes";
  else
    messageString ="minute";
}

string Registrar::studentMessage()
{
  if (totalStuds != 1)
    return (" students were helped.\nInformation:");
  else
    return (" student was helped.\nInformation:");
}
