// TODO: Write file header comment.

#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include<fstream>
#include<math.h>
#include "driver.h"

using namespace std;

int options();
int selecttest();
string Test(int number);
string TestSwitch(int number);
float SCORES[10]={0,0,0,0,0,0,0,0,0,0};
string FACTORS[2];
string VALUE[2];
float cosinesimilarity();
float normalize(int O,int C,int E,int A,int N);
void EvaluateO(int option,int weightage);
void EvaluateC(int option,int weightage);
void EvaluateE(int option,int weightage);
void EvaluateA(int option,int weightage);
void EvaluateN(int option,int weightage);
void normalizescore1();
void normalizescore2();
int getmax(float difference[],int i);
string readquestions(int number);
string getresult(string file);
void minimize(int option,string factors);
void categorize(string rest,string first);
void divide(string first, string second,string third,string fourth,string fifth);
void evaluate(int option,int status,string factor1,string weightage1,string factor2,string weightage2);

int main() {//MAIN FUNCTION, EXECUTION STARTS HERE
    int answer;
    int position;
    string question;
    string result;
    int numOfQuestions;
    int testnumber;//DECLARING VARIBLES

    cout<<"Welcome to the Personality Quiz!"<<endl;
    cout<<"\nChoose number of questions: ";//PRINTING MESSAGE
    cin>>numOfQuestions;//ASKING FOR NUMBER OF QUESTIONS

    for(int i=0;i<numOfQuestions;i++)//looping to get the questions
    {
        cout<<"\nHow much do you agree with this statement?"<<endl;
        question=readquestions(numOfQuestions);
        position = question.find(".");
        string temp=question.substr(position+2);
        question=question.substr(0,position+1);

        cout<<"\""<<question<<"\""<<endl;
        answer=options();
        minimize(answer,temp);
    }

    while(1)//INFINITE LOOP TO PRINT TEST TYPES
    {
        testnumber=selecttest();//CALLING FUNCTION
        result=Test(testnumber);//CALLING FUNCTION
        cout<<"You got "<<result<<"!"<<endl;//PRINTING RESULT
    }
    return 0;//RETURNING
}//END OF MAIN


//FUNCTION TO CREATE ASSIGN NUMBERS TO CORRESPONDING FACTOR
//TAKES TWO ARGUMENTS, RETURNS NOTHING
void categorize(string rest,string first){

        if(rest=="O"){//IF ITS O
            SCORES[5]=stoi(first);
        }
        else if(rest=="C"){//IF ITS C
            SCORES[6]=stoi(first);
        }
        else if(rest=="E"){//IF ITS E
            SCORES[7]=stoi(first);
        }
        else if(rest=="A"){//IF ITS A
            SCORES[8]= stoi(first);
        }
        else if(rest=="N"){//IF ITS N
            SCORES[9]=stoi(first);
        }
}//END IOF FUNCTION

//FUNCTION TO DIVIDE A FACTOR STRING TO CORRESPONDING VALUE & FACTOR
//TAKES ALL THE FACTORS,RETURNS NOTHING
void divide(string first, string second,string third,string fourth,string fifth){
    int position;
    string rest[5];//DECLARING VARIABLES

    position = first.find(":");//GETTING POSITION OF : IN STRING
    rest[0]=first.substr(0,position);
    first=first.substr(position+1);//GETTING FIRST FACTOR OF A STRING FROM PEOPLES FILE
    categorize(rest[0],first);//CALLING FUNCTION

    position = second.find(":");//GETTING POSITION OF : IN STRING
    rest[1]=second.substr(0,position);
    second=second.substr(position+1);//GETTING SECOND FACTOR OF A STRING FROM PEOPLES FILE
    categorize(rest[1],second);//CALLING FUNCTION

    position = third.find(":");//GETTING POSITION OF : IN STRING
    rest[2]=third.substr(0,position);
    third=third.substr(position+1);//GETTING THIRD FACTOR OF A STRING FROM PEOPLES FILE
    categorize(rest[2],third);//CALLING FUNCTION

    position = fourth.find(":");//GETTING POSITION OF : IN STRING
    rest[3]=fourth.substr(0,position);
    fourth=fourth.substr(position+1);//GETTING FOURTH FACTOR OF A STRING FROM PEOPLES FILE
    categorize(rest[3],fourth);//CALLING FUNCTION

    position = fifth.find(":");//GETTING POSITION OF : IN STRING
    rest[4]=fifth.substr(0,position);
    fifth=fifth.substr(position+1);//GETTING FIFTH FACTOR OF A STRING FROM PEOPLES FILE
    categorize(rest[4],fifth);//CALLING FUNCTION
}//END OF FUNCTION

//FUNCTION TO NORMALIZE SCORES
//TAKES ALL THE RESPECTIVE SCORES, RETURNS FLOATING NORMALIZED SCORE
float normalize(int O,int C,int E,int A,int N){
    float number;
    float V=O*O;
    float W=C*C;
    float X=E*E;
    float Y=A*A;
    float Z=N*N;//GETTING SQUARES
    float sum=V+W+X+Y+Z;//SUMMING UP ALL SQUARES

    sum=pow(sum,0.5);//TAKING SQUARE ROOT
    number=O/sum;//NORMALIZING

    return number;//RETURNING NORMALIZED FORM
}//END OF FUNCTION

//FUNCTION TO NORMALIZE SCORES
//TAKES NOTHING, RETURNS NOTHING
void normalizescore1()
{
    SCORES[0]=normalize(SCORES[0],SCORES[1],SCORES[2],SCORES[3],SCORES[4]);
    SCORES[1]=normalize(SCORES[1],SCORES[0],SCORES[2],SCORES[3],SCORES[4]);
    SCORES[2]=normalize(SCORES[2],SCORES[1],SCORES[0],SCORES[3],SCORES[4]);
    SCORES[3]=normalize(SCORES[3],SCORES[1],SCORES[2],SCORES[0],SCORES[4]);
    SCORES[4]=normalize(SCORES[4],SCORES[1],SCORES[2],SCORES[3],SCORES[0]);
}//END OF FUNCTION

//FUNCTION TO NORMALIZE SCORES
//TAKES NOTHING, RETURNS NOTHING
void normalizescore2()
{
    SCORES[5]=normalize(SCORES[5],SCORES[6],SCORES[7],SCORES[8],SCORES[9]);
    SCORES[6]=normalize(SCORES[6],SCORES[5],SCORES[7],SCORES[8],SCORES[9]);
    SCORES[7]=normalize(SCORES[7],SCORES[6],SCORES[5],SCORES[8],SCORES[9]);
    SCORES[8]=normalize(SCORES[8],SCORES[6],SCORES[7],SCORES[5],SCORES[9]);
    SCORES[9]=normalize(SCORES[9],SCORES[6],SCORES[7],SCORES[8],SCORES[5]);
}//END OF FUNCTION

string getresult(string file){
    int j=0;
    int i=0;
    string O,C,E,A,N;
    int position;
    string result;
    string rest[25];
    string names[25];
    float difference[25];
    string line[25];//DECLARING VARIABLES
    const map<char, double> lhs;
    const map<char, double> rhs;

    normalizescore1();

    std::ifstream openfile(file);//OPRNING FILE
    std::string str;

    while (std::getline(openfile, str))//READING FILE
    {
       line[i]=str;
       i++;
    }
    openfile.close();//CLOSING FILE

    for(int count=0;count<i;count++)
    {
         position = line[count].find(".");
         names[count]=line[count].substr(0,position);
         rest[count]=line[count].substr(position+2);

         position = rest[count].find(" ");
         O= rest[count].substr(0,position);
         rest[count]=rest[count].substr(position+1);

         position = rest[count].find(" ");
         C= rest[count].substr(0,position);
         rest[count]=rest[count].substr(position+1);

         position = rest[count].find(" ");
         E= rest[count].substr(0,position);
         rest[count]=rest[count].substr(position+1);

         position = rest[count].find(" ");
         A= rest[count].substr(0,position);
         rest[count]=rest[count].substr(position+1);

         position = rest[count].find(" ");
         N= rest[count].substr(0,position);
         rest[count]=rest[count].substr(position+1);

         divide(O,C,E,A,N);
         normalizescore2();
         difference[count]=cosinesimilarity();
         //difference[count]=cosineSimilarityOf(lhs,rhs);
    }
    result=names[getmax(difference,i)];

    return result;
}

//FUNCTION TO GET MAXIMUM
//TAKES TWO ARGUMENTS, RETURNS INDEX
int getmax(float difference[],int i)
{
    int index=0;
    int temp = difference[0];
    for(int j=0; j<i; j++) {
      if(temp<difference[j]) {
         temp=difference[j];
         index++;
      }
    }

    return index;
}//END OF FUNCTION


//FUNCTION TO GET TEST RESULTS
//TAKES TEST NUMBER,CHOOSEN FORM MENU
//RETURNS RESULT
string Test(int number)
{
    string result;
    result=TestSwitch(number);
    return result;
}//END OF FUNCTION

//FUNCTION TO GET TEST RESULTS
//TAKES TEST NUMBER,CHOOSEN FORM MENU
//RETURNS RESULT
string TestSwitch(int number)
{
        switch(number){//SWITCH CASE TO SWITCH THROUGH PEOPLE FILES
        case 1:{
            return getresult("BabyAnimals.PEOPLE");//IF OPTION 1 SELECTED
            break;}
        case 2:{
            return getresult("Brooklyn99.PEOPLE");//IF OPTION 2 SELECTED
            break;}
        case 3:{
            return getresult("Disney.PEOPLE");//IF OPTION 3 SELECTED
            break;}
        case 4:{
            return getresult("Hogwarts.PEOPLE");//IF OPTION 4 SELECTED
            break;}
        case 5:{
             return getresult("MyersBriggs.PEOPLE");//IF OPTION 5 SELECTED
             break;}
        case 6:{
             return getresult("SesameStreet.PEOPLE");//IF OPTION 6 SELECTED
             break;}
        case 7:{
             return getresult("StarWars.PEOPLE");//IF OPTION 7 SELECTED
             break;}
        case 8:{
             return getresult("Vegetables.PEOPLE");//IF OPTION 8 SELECTED
             break;}
        case 9:{
             return getresult("mine.PEOPLE");//IF OPTION 9 SELECTED
             break;}
    }//END OF SWITCH
}//END OF FUNCTION

//FUNCTION TO PRINT TESTS
//TAKES NOTHING, RETURNS TEST SELECTED
int selecttest()//START OF FUNCTION
{
    int selecttest;//DECLARING VARIBALES
    cout<<"\n";
    cout<<"1. BabyAnimals"<<endl;
    cout<<"2. Brooklyn99"<<endl;
    cout<<"3. Disney"<<endl;
    cout<<"4. Hogwarts"<<endl;
    cout<<"5. MyersBriggs"<<endl;
    cout<<"6. SesameStreet"<<endl;
    cout<<"7. StarWars"<<endl;
    cout<<"8. Vegetables"<<endl;
    cout<<"9. mine"<<endl;
    cout<<"0. To end program."<<endl;//PRINTING OPTINS/TESTS

    cout<<"\nChoose test number (1-9, or 0 to end): ";//PRINTING MESSAGE
    cin>>selecttest;//GETTING INPUT

    if(selecttest==0){//ID ZERO IS ENTERED, QUIT THE PROGRAM
        cout<<"Goodbye!"<<endl;//PRINTING MESSAGE
        exit(1);//EXIT
    }
    return selecttest;//RETURNING OPTION SELECTED
}//END OF FUNCTION

//FUNCTION TO READ QUESTIONS FILE
//TAKES NUMBER OF QUESTIONS TO BE ASKED
//RETURNS QUESTION
string readquestions(int number)
{
    int i=0;
    int random;
    string questions[486];//DECLARING VARIABLES

    std::ifstream file("questions.txt");//OPENING FILE
    std::string str;

    while (std::getline(file, str))//READING LINE
    {
       questions[i]=str;//READING A LINE AND PLACINF IN ARRAY
       i++;
    }
    file.close();//CLOSING FILE

    random=randomInteger(0,485);//GETTING RANDOM NUMBER
    return questions[random];//RETURNING RANDOM QUESTION
}//END OF FUNCTION*/

//FUNCTION TO PRINT OPTIONS
//TAKES NOTHING, RETURNS OPTION SELECTED
int options()//START OF FUNCTION
{
    int answer;//DECLARING VARIABLES
    cout<<"\n";
    cout<<"1. Strongly disagree"<<endl;
    cout<<"2. Disagree"<<endl;
    cout<<"3. Neutral"<<endl;
    cout<<"4. Agree"<<endl;
    cout<<"5. Strongly agree"<<endl;//PRINTING OPTIONS

    cout<<"\nEnter your answer here (1-5): ";//PRINTING MESSAGE
    cin>>answer;//GETTING INPUT
    return answer;//RETURNOING OPTION SELECTED
}//END OF FUNCTION

//FUNCTION TO GET COSINE SIMILARITY
//TAKES NOTHING, RETURNS FLOAT
float cosinesimilarity()
{
    float first;
    float second;
    float third;
    float fourth;
    float fifth;
    float sum;//DECLARING VARIABLES

    first=SCORES[0]*SCORES[5];
    second=SCORES[1]*SCORES[6];
    third=SCORES[2]*SCORES[7];
    fourth=SCORES[3]*SCORES[8];
    fifth=SCORES[4]*SCORES[9];//GETTING PRODUCT OF CORRESPONDING VALUES

    sum=first+second+third+fourth+fifth;//SUMMING UP
    return sum;//RETURNING SUM
}//END OF FUNCTION*/

//FUNCTION TO GET SCORES FOR FACTOR O
//TAKES OPTION SELECTED & WEIGHT
//RETURND NOTHING
void EvaluateO(int option,int weightage)
{
    if(weightage>0){//IF WEIGHT IS POSITIVE
        if(option==1)//STRONGLY DISAGREE SELECTED
            SCORES[0]-=2;
        else if(option==2)//DISAGREE SELECTED
            SCORES[0]-=1;
        else if(option==3)//NEUTRAL
            SCORES[0]+=0;
        else if(option==4)//AGREE SELECTED
            SCORES[0]+=1;
        else if(option==5)//STRONGLY AGREE SELECTED
            SCORES[0]+=2;
    }
    else if(weightage<0){//IF WEIGHT IS NEGATIVE
        if(option==1)//STRONGLY DISAGRESS SELECTED
            SCORES[0]+=2;
        else if(option==2)//DISAGREE SELECTED
            SCORES[0]+=1;
        else if(option==3)//NEUTRAL
            SCORES[0]+=0;
        else if(option==4)//AGREE SELECTED
            SCORES[0]-=1;
        else if(option==5)//STRONGLY AGREE SELECTED
            SCORES[0]-=2;
    }
}//END OF FUNCTION

//FUNCTION TO GET SCORES FOR FACTOR C
//TAKES OPTION SELECTED & WEIGHT
//RETURND NOTHING
void EvaluateC(int option,int weightage)
{
    if(weightage>0){//IF WEIGHT IS POSITIVE
        if(option==1)//STRONGLY DISAGRESS SELECTED
            SCORES[1]-=2;
        else if(option==2)//DISAGREE SELECTED
            SCORES[1]-=1;
        else if(option==3)//NEUTRAL
            SCORES[1]+=0;
        else if(option==4)//AGREE SELECTED
            SCORES[1]+=1;
        else if(option==5)//STRONGLY AGREE SELECTED
            SCORES[1]+=2;
    }
    else if(weightage<0){//IF WEIGHT IS NEGATIVE
        if(option==1)//STRONGLY DISAGRESS SELECTED
            SCORES[1]+=2;
        else if(option==2)//DISAGREE SELECTED
            SCORES[1]+=1;
        else if(option==3)//NEUTRAL
            SCORES[1]+=0;
        else if(option==4)//AGREE SELECTED
            SCORES[1]-=1;
        else if(option==5)//STRONGLY AGREE SELECTED
            SCORES[1]-=2;
    }
}//END OF FUNCTION

void EvaluateE(int option,int weightage)
{
    if(weightage>0){//IF WEIGHT IS POSITIVE
        if(option==1)//STRONGLY DISAGRESS SELECTED
            SCORES[2]-=2;
        else if(option==2)//DISAGREE SELECTED
            SCORES[2]-=1;
        else if(option==3)//NEUTRAL
            SCORES[2]+=0;
        else if(option==4)//AGREE SELECTED
            SCORES[2]+=1;
        else if(option==5)//STRONGLY AGREE SELECTED
            SCORES[2]+=2;
    }
    else if(weightage<0){//IF WEIGHT IS NEGATIVE
        if(option==1)//STRONGLY DISAGRESS SELECTED
            SCORES[2]+=2;
        else if(option==2)//DISAGREE SELECTED
            SCORES[2]+=1;
        else if(option==3)//NEUTRAL
            SCORES[2]+=0;
        else if(option==4)//AGREE SELECTED
            SCORES[2]-=1;
        else if(option==5)//STRONGLY AGREE SELECTED
            SCORES[2]-=2;
    }
}//END OF FUNCTION

void EvaluateA(int option,int weightage)
{
   if(weightage>0){//IF WEIGHT IS POSITIVE
        if(option==1)//STRONGLY DISAGRESS SELECTED
            SCORES[3]-=2;
        else if(option==2)//DISAGREE SELECTED
            SCORES[3]-=1;
        else if(option==3)//NEUTRAL
            SCORES[3]+=0;
        else if(option==4)//AGREE SELECTED
            SCORES[3]+=1;
        else if(option==5)//STRONGLY AGREE SELECTED
            SCORES[3]+=2;
    }
    else if(weightage<0){//IF WEIGHT IS NEGATIVE
        if(option==1)//STRONGLY DISAGRESS SELECTED
            SCORES[3]+=2;
        else if(option==2)//DISAGREE SELECTED
            SCORES[3]+=1;
        else if(option==3)//NEUTRAL
            SCORES[3]+=0;
        else if(option==4)//AGREE SELECTED
            SCORES[3]-=1;
        else if(option==5)//STRONGLY AGREE SELECTED
            SCORES[3]-=2;
    }
}//END OF FUNCTION

void EvaluateN(int option,int weightage)
{
    if(weightage>0){//IF WEIGHT IS POSITIVE
        if(option==1)//STRONGLY DISAGRESS SELECTED
            SCORES[4]-=2;
        else if(option==2)//DISAGREE SELECTED
            SCORES[4]-=1;
        else if(option==3)//NEUTRAL
            SCORES[4]+=0;
        else if(option==4)//AGREE SELECTED
            SCORES[4]+=1;
        else if(option==5)//STRONGLY AGREE SELECTED
            SCORES[4]+=2;
    }
    else if(weightage<0){//IF WEIGHT IS NEGATIVE
        if(option==1)//STRONGLY DISAGRESS SELECTED
            SCORES[4]+=2;
        else if(option==2)//DISAGREE SELECTED
            SCORES[4]+=1;
        else if(option==3)//NEUTRAL
            SCORES[4]+=0;
        else if(option==4)//AGREE SELECTED
            SCORES[4]-=1;
        else if(option==5)//STRONGLY AGREE SELECTED
            SCORES[4]-=2;
    }
}//END OF FUNCTION

//FUNCTION TO CALL EVALUATION FUNCTIONS
//TAKES FACTORS & THEIR WEIGHTAGE. RETURNS NOTHING
void evaluate(int option,int status,string factor1,string weightage1,string factor2,string weightage2)
{
    if(status==1){//IF STATUS 1, ONLY 1 FACTOR
            if(factor1=="O"){
                EvaluateO(option,stoi(weightage1));//EVALUATING O
            }
            else if(factor1=="C"){
                EvaluateC(option,stoi(weightage1));//EVALUATING C
            }
            else if(factor1=="E"){
                EvaluateE(option,stoi(weightage1));//EVALUATING E
            }
            else if(factor1=="A"){
                EvaluateA(option,stoi(weightage1));//EVALUATING A
            }
            else if(factor1=="N"){
                EvaluateN(option,stoi(weightage1));//EVALUATING N
            }
    }//END OF IF
    else if(status==2){//IF STATUS 2, 2 FACTORS
            if(factor1=="O"){
                EvaluateO(option,stoi(weightage1));//EVALUATING O
            }
            else if(factor1=="C"){
                EvaluateC(option,stoi(weightage1));//EVALUATING C
            }
            else if(factor1=="E"){
                EvaluateE(option,stoi(weightage1));//EVALUATING E
            }
            else if(factor1=="A"){
                EvaluateA(option,stoi(weightage1));//EVALUATING A
            }
            else if(factor1=="N"){
                EvaluateN(option,stoi(weightage1));//EVALUATING N
            }

            if(factor2=="O"){
                EvaluateO(option,stoi(weightage2));//EVALUATING O
            }
            else if(factor2=="C"){
                EvaluateC(option,stoi(weightage2));//EVALUATING C
            }
            else if(factor2=="E"){
                EvaluateE(option,stoi(weightage2));//EVALUATING E
            }
            else if(factor2=="A"){
                EvaluateA(option,stoi(weightage2));//EVALUATING A
            }
            else if(factor2=="N"){
                EvaluateN(option,stoi(weightage2));//EVALUATING N
            }
    }//END OF IFELSE
}//END OF FUNCTION

//FUNCTION TO CREATED SUBSTRINGS OF QUESTION ASKED
//TAKES OPTION SELECTED & FACTOR STRING
//RETURNS NOTHING
void minimize(int option, string factors)
{
    string factor1="";
    string weightage1="";
    string factor2="";
    string weightage2="";
    string tempfactor="";
    int position;
    int status;//DECLARING VARIABELS

    if(factors.length()==3|| factors.length()==4){//IF LENGTH OF STRING IS BETWEEN 3 & 4--> ONLY 1 FACTOR
        status=1;
        position = factors.find(":");
        factor1=factors.substr(0,position );
        weightage1=factors.substr(position+1,position+2);
        FACTORS[0]=factor1;
        VALUE[0]=weightage1;
        evaluate(option,1,factor1,weightage1,"0","0");//CALLING FUNCTION
    }
    else{//ELSE TWO OR MORE FACTORS
        status=2;
        position = factors.find(":");
        factor1=factors.substr(0,position );
        weightage1=factors.substr(position+1,position+2);

        FACTORS[0]=factor1;
        VALUE[0]=weightage1;

        position = factors.find(" ");
        tempfactor=factors.substr(position+1);

        position = tempfactor.find(":");
        factor2=tempfactor.substr(0,position );
        weightage2=tempfactor.substr(position+1,position+2);

        position = weightage1.find(" ");
        weightage1=weightage1.substr(0,position);

        FACTORS[1]=factor2;
        VALUE[1]=weightage2;
        evaluate(option,2,factor1,weightage1,factor2,weightage2);//CALLING FUNCTION
    }
}//END OF FUNCTION
