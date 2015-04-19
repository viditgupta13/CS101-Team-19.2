#include <simplecpp>
#include <graphics.h>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
class Akinator//starting of class definition
{
public:
    string characters[92][20];//to store database
    string questions[19][3];//to store questions
    string line1;
    string line2;
    int n;//stores the number of characters left
    int index;//points to question number
    Akinator()//default constructor
    {   //loading of database and questions in arrays starts
        ifstream infile1("names.txt");
        ifstream infile2("output.txt");
        for(int i=0;i<92;i++)
        {
            getline(infile1, line1);
            getline(infile2, line2);
            string line=line1+line2;
            int j=0;
            string word="";
            for(int k=0;k<line.length();k++)
            {
                if(line[k]=='&')//seperator used is '&'
                {
                    characters[i][j]=word;
                    j++;
                    word="";
                }
                else
                    word=word+line[k];
            }
         }
         infile1.close();
         infile2.close();//closing database files
         ifstream infile3("questions.txt");
         for(int i=0;i<19;i++)
         {
            getline(infile3, line1);
            int j=0;
            string word="";
            for(int k=0;k<line1.length();k++)
            {
                if(line1[k]=='&')
                {
                    questions[i][j]=word;
                    j++;
                    word="";
                }
                else
                    word=word+line1[k];
            }
         }
         infile3.close();//closin
         n=92;//initialize with number of characters+1
         index=11;//initialie with starting question's serial number
    }
    char display(string &s)
    {
        char c;
        settextstyle(10,0,1);//changes text style,rotation,font size respectively
        Rectangle questionScreen(250,150,textWidth(s)+5,textHeight()+2);//encloses question
        Text q(250,150,s);//prints question on the canvas with it's centre as (250,150)

        Rectangle r(100,300,textWidth("YES")+40,textHeight()+40);
        r.setFill(true);
        r.setColor(COLOR(0,250,0));//sets color of YES block to green
        Text ty(100,300,"YES");

        Rectangle r1(400,300,textWidth("NO")+40,textHeight()+40);
        r1.setFill(true);
        r1.setColor(COLOR(250,0,0));//sets color of NO block to red
        Text tn(400,300,"NO");

        Rectangle r2(250,400,textWidth("DON'T KNOW")+40,textHeight()+40);
        r2.setFill(true);
        r2.setColor(COLOR(0,0,250));//sets color of DON'T KNOW to blue
        Text td(250,400,"DON'T KNOW");


        double xy,yy,xn,yn,xd,yd;
        xy=textWidth("YES");//these two commands tell the width and height of the text
        yy=textHeight();
        xn=textWidth("NO");
        yn=textHeight();
        xd=textWidth("DON'T KNOW");
        yd=textHeight();
        int cl=getClick();//this click determines the response
        double x,y;
        x=cl/65536;
        y=cl%65536;
        if(x>100-xy/2-40 && x<100+xy/2+40 && y<300+yy/2+40 && y>300-yy/2-40)//response is taken according to the click position
            c='y';
        if(x>400-xn/2-40 && x<400+xn/2+40 && y<300+yn/2+40 && y>300-yn/2-40)
            c='n';
        if(x>250-xd/2-40 && x<250+xd/2+40 && y<400+yn/2+40 && y>400-yn/2-40)
            c='d';
        return c;
    }
    void responseYes(int i, int &n , int index, string characters[][20], string quality[])//function executed when yes response given
    {
        for(int j=1;j<n;j++)
        {
            if(characters[j][index+1]!=quality[i])//delete those characters whose entries do not match with quality[i]
            {
                for(int k=j;k<n-1;k++)
                {
                    for(int l=0;l<20;l++)
                        characters[k][l]=characters[k+1][l];//deleting characters
                }
                j--;
                n--;//updating database size
            }
        }
    }
    void responseNo(int i, int &n, int index, string characters[][20], string quality[])//function executed when no response is given
    {
        for(int j=1;j<n;j++)
        {
            if(characters[j][index+1]==quality[i])//delete those characters whose entries match with quality[i]
            {
                for(int k=j;k<n-1;k++)
                {
                    for(int l=0;l<20;l++)
                        characters[k][l]=characters[k+1][l];//deleting characters
                }
                j--;
                n--;//updating database size
            }
        }
    }
    int getArray(string quality[], int frequency[], int index, int n)//returns number of variations in quality
    {
        int s=0;//variable to be returned
                for(int j=1;j<n;j++)//j moves through a column
                {
                    int flag=0;//flag stores whether a quality has been repeated before
                    for(int k=0;k<s;k++)
                    {
                        if(quality[k]==characters[j][index+1])//stores if quality has been stored before
                        {
                            flag=1;
                            break;
                        }
                    }
                    if(flag==0)//if qualityb is not repeated
                    {
                        int c=0;//stores frequency
                        for(int a=j;a<n;a++)
                        {
                            if(characters[j][index+1]==characters[a][index+1])
                                c++;//frequency increased if quality is repeated
                        }
                        quality[s]=characters[j][index+1];
                        frequency[s]=c;
                        s++;//increase actual size of arrays
                        c=0;//reset counter
                    }//end of if(flag==0)
                }//end of outer for loop
                return s;
    }
    void sortArray(string quality[], int frequency[], int sizeArray)//sorting arrays using selection sort technique
    {
        for(int i=0;i<sizeArray-1;i++)
        {
            for(int j=i+1;j<sizeArray;j++)
            {
                if(frequency[i]<frequency[j])//if there is a larger element in the sub array exchange position
                {
                    int temp1=frequency[i];
                    frequency[i]=frequency[j];
                    frequency[j]=temp1;
                    string temp2=quality[i];
                    quality[i]=quality[j];
                    quality[j]=temp2;
                }
            }
        }
    }
    string mainAkinator()//recursive funcction which returns final result
    {
        string quality[40];//stores the variations of an attribute
        int frequency[40];//stores the corresponding frequency of the variation
        int sizeArray=getArray(quality, frequency, index, n);//sizeArray will store actual size of arrays quality and frequency
        for(int i=0;i<sizeArray;i++)//start of for looop
        {
            string q=questions[index][1]+quality[i]+"?";
            char res=display(q);//question sent to canvas
            if(res=='y')//if answer is yes
            {
                responseYes(i, n, index, characters, quality);//function call to make corresponding deletions in database and change in n
                if(n==1)//if no character is left
                    return "No character";
                if(n==2)//if only one character is left
                    return characters[1][1];
                if(quality[i]=="a cricketer")//special case for first question
                    index=4;
                if(quality[i]=="a politician")
                    index=7;
                else
                    istringstream(questions[index][2]) >> index;//update index with SI No of next question
                if(index==0)//if all questions are exhausted end game
                    break;
                return mainAkinator();//recursive call
            }
            else if(res=='n')//if answer is no
            {
                responseNo(i, n, index, characters, quality);//function call to make corresponding deletions in database and change in n
                if(n==1)//if no character is left
                    return "No character";
                if(n==2)//if only one character is left
                    return characters[1][1];
            }
            else if(res=='d')//if answer is don't know
            {
                if(i==sizeArray-1)//if list of attributes is exhausted, go to next question
                {
                    istringstream(questions[index][2]) >> index;//update index with SI No of next question
                    if(index==0)//if all questions are exhausted end game
                        break;
                    return mainAkinator();//recursive call
                }
                else
                    continue;//go to next attribute
            }
        }//end of for
        return "No character";
    }
};//end of class definition
int main()
{
    initCanvas("Akinator",500,500);//creates a canvas of dimension 500x500 on which the player is supposed to play

    Rectangle mainScreen(250,250,500,500);
    settextstyle(10,0,4);
    mainScreen.setFill(true);
    mainScreen.setColor(COLOR(0,0,0));//sets the color of canvas to black

    int Click;//this click begins the game
    Rectangle r2(250,250,textWidth("WELCOME")+5,textHeight()+2);
    settextstyle(6,0,3);
    Text t2(250,250,"WELCOME");
    Click=getClick();
    t2.hide();
    r2.hide();
    Text t1(250,250,"Akinator Begins!!!");
    Rectangle r1(250,250,textWidth("Akinator Begins!!!")+5,textHeight()+2);
    Click=getClick();
    t1.hide();
    r1.hide();
    Rectangle r3(250,75,textWidth("PLAY")+5,textHeight()+5);
    Text t3(250,75,"PLAY");

    Rectangle r4(250,250,textWidth("INSTRUCTIONS")+5,textHeight()+5);
    Text t4(250,250,"INSTRUCTIONS");
    Rectangle r5(250,425,textWidth("EXIT")+5,textHeight()+5);
    Text t5(250,425,"EXIT");
    int x1=textWidth("PLAY"),y1=textHeight();
    int x2=textWidth("INSTRUCTIONS"),y2=textHeight();
    int x3=textWidth("EXIT"),y3=textHeight();
    bool check=true;
    int Click1;

    while(check)
    {
        Click1=getClick();//this click tells the choice of the player
        t3.hide();
        r3.hide();
        t4.hide();
        r4.hide();
        t5.hide();
        r5.hide();
        if ((Click1/65536>(250-(x1/2))) && (Click1/65536<(250+(x1/2))) && (Click1%65535>(75-(y1/2))) && (Click1%65536<(75+(y1/2))))
        {//if click is inside "PLAY' button
            Akinator obj;
            string result1;
            result1=obj.mainAkinator();
            Rectangle res(250,250,textWidth(result1)+5,textHeight()+2);
            Text result(250,250,result1);

            Rectangle restart(50,450,textWidth("RESTART")+5,textHeight()+2);
            Text rest(50,450,"RESTART");
            int x7=textWidth("RESTART");
            int y7=textHeight();


            int Click4;
            while(true)
            {
                if(result1=="No character")//if player doesn't get back any character, he is asked to enter the character he had thought of
                {
                    Text t13(250,350,"What character did you think of?");

                    Rectangle r12(370,450,textWidth("Enter your character"),textHeight());
                    Text t12(370,450,"Enter your character");
                    int x12=textWidth("Enter your character");
                    int y12=textHeight();

                    Click4=getClick();
                    if(Click4/65536>(50-(x7/2))  &&  Click4/65536<(50+(x7/2))  && Click4%65536 >(450-(y7/2)) && Click4%65536 <(450+(y7/2)))
                        break;//if click is inside 'Restart' button
                    else if(Click4/65536>(400-(x12/2))  &&  Click4/65536<(400+(x12/2))  && Click4%65536 >(450-(y12/2)) && Click4%65536 <(450+(y12/2)))
                    {//if click is inside 'Enter your character' button
                        res.hide();
                        result.hide();
                        restart.hide();
                        rest.hide();
                        r12.hide();
                        t12.hide();
                        t13.hide();

                        string input;//takes in name of character from console
                        Text t11(250,250,"Enter your character in console");
                        cout << "Enter your character" << endl;
                        getline(cin,input);
                        string password;//enter password
                        cout << "Enter password" << endl;

                        getline(cin,password);//input password
                        //cout << password;
                        if(password=="helloworld")//if password matches
                        {
                            ofstream outfile("names1.txt", ios::app);
                            outfile << input;//add name to file for later addition to database
                            outfile.close();
                            cout << "Input successful";
                        }
                        else
                            cout << "Wrong password";
                    }
                }
                else//if you get back a character then player can restart the game
                {
                    Click4=getClick();
                    if(Click4/65536>(50-(x7/2))  &&  Click4/65536<(50+(x7/2))  && Click4%65536 >(450-(y7/2)) && Click4%65536 <(450+(y7/2)))
                        break;//if click is inside 'Restart' button
                }
            }
            settextstyle(6,0,3);
        }

        else if((Click1/65536>(250-(x2/2))) && (Click1/65536<(250+(x2/2))) && (Click1%65535>(250-(y2/2))) && (Click1%65536<(250+(y2/2))))
        {//if click is inside 'INSTRUCTION' button
            settextstyle(1,0,1);
            Text inst(250,50,"The player has to think of a character.");
            Text inst1(250,100,"The Akinator will ask a series of ");
            Text inst2(250,150,"questions.Based on the responses ");
            Text inst3(250,200,"given by the player,the Akinator");
            Text inst4(250,250,"will attempt to guess the character.The");
            Text inst5(250,300,"response has to be given in either Yes,");
            Text inst6(250,350,"No or Don't Know.Note that the database");
            Text inst7(250,400," is restricted to certain characters.");

            Rectangle b(50,50,textWidth("Back")+10,textHeight()+10);
            Text bt(50,450,"Back");
            int x4=textWidth("Back"),y4=textHeight();


            bool backCheck =true;



            int Click2;
            while(backCheck)//if player clicks at the back button
            {
                Click2=getClick();
                if((Click2/65536>(50-(x4/2))) && (Click2/65536<(50+(x4/2))) && (Click2%65535>(450-(y4/2))) && (Click2%65536<(450+(y4/2))))
                    backCheck=false;
            }
            settextstyle(6,0,3);
        }

        else if(Click1/65536>(250-(x3/2)) && Click1/65536<(250+(x3/2)) && Click1%65535>(425-(y3/2)) && Click1%65536<(425+(y3/2)))
        {//if player clicks inside "EXIT' button
            check=false;
            break;
        }

    t3.show();
    r3.show();
    t4.show();
    r4.show();
    t5.show();
    r5.show();
    }
}
