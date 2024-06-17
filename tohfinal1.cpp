#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<string.h>
#include<string>
#include<math.h>
#define cm -10


//657 ma milako
using namespace std;
int top1=-1;    //1st stack
int top2=-1;    //2nd stack
int top3=-1;    //3rd stack
int peg1[10];   //stack for peg 1
int peg2[10];   //stack for peg 2
int peg3[10];   //stack for peg 3
int steps=0;    //counter to count number of moves
int maxsteps;   //counter to count number of remaining moves
char maxstepstring[20]; //string of counter to display number of remaining move in graphic window
char numberstring[20];  //string of counter to display  number of move in graphic window
char maxmovestring[20]="Remaining move ="; //remaining move
char steptxt[10]="Steps =";  //to display steps in graphic window
int number; //number of disks taken from user
int mx1;    //mouse pointer of second click in x-coordinate
int my1;    //mouse pointer of second click in y-coordinate
int mx2;    //mouse pointer of first click in x-coordinate
int my2;    //mouse pointer of first click in y-coordinate
bool reg1=false,reg2=false;   //mouse click register check bool
void push(char peg,int data); // stack push operation function
int pop(char peg);            // stack pop operation function
void mouseclick();            // start menu mouse click receiver
void start();                 // function to be called when start is clicked
void help();                  // function to be called when help is clicked
void exit();                  // function to be called when exit is clicked
void mainmenu()               //display start help exit in main menu
{
    readimagefile("newmainmenu.JPG", 0, 0, getmaxx(), getmaxy());//background image
    setfillstyle(1,RGB(255,183,197));       //bar bhitra 1 pattern ma rgb color halyo
    setcolor(RGB(255,183,197));
    //start ko
    bar(600,330,950,410);
    pieslice(600,330,90,180,5);    //top left
    pieslice(600,410,180,270,5);   //bottom left
    pieslice(950,330,0,90,5);      //top right
    pieslice(950,410,270,0,5);     //bottom right
    bar(600,325,950,415);           //top and bottom
    bar(595,330,955,410);           //left and right
    //help ko
    bar(650,470,930,550);
    pieslice(650,470,90,180,5);     //top left
    pieslice(650,550,180,270,5);    //bottom left
    pieslice(930,470,0,90,5);       //top right
    pieslice(930,550,270,0,5);      //bottom right
    bar(650,465,930,555);           //top and bottom
    bar(645,470,935,550);           //left and right
    //exit ko
    bar(650,610,905,690);
    pieslice(650,610,90,180,5);     //top left
    pieslice(650,690,180,270,5);        //bottom left
    pieslice(905,610,0,90,5);           //top right
    pieslice(905,690,270,0,5);          //bottom right
    bar(650,605,905,695);       //top and bottom
    bar(645,610,910,690);       //left and right
    setcolor(BLACK);
    setbkcolor(RGB(255,183,197));
    settextstyle(1,0,7);            //text ko pattern
    outtextxy(605,340,"START");
    outtextxy(655,480,"HELP");
    outtextxy(655,620,"EXIT");
    mouseclick();
}

void mouseclick()
{
    //point is the structure that represent two dimensional space.It is used to store the x and y co-ordinate of a point
    POINT cursorposition;       //point type ko cursorposition variable banako
    int mx,my;
    while(1)
    {
        GetCursorPos(&cursorposition);      //getcursorpos le get the current position of the cursor and store it in the cursorposition variable
        mx=cursorposition.x;                //x axis ko point mx ma store hunxa
        my=cursorposition.y;                //y axis ko point

        if(GetAsyncKeyState(VK_LBUTTON))        //check if the mouse ko left buttom click bha xa ki nai
        {
            if((mx>=595 && mx<=955)&&(my>=325 && my<=415))      //check garxa diyeko axis bhitra xa ki xna
            {
                start();                                        //left botton click garxa teti bhitra click garyo bhane start call hunxa
                break;
            }

            if((mx>=645 && mx<=945)&&(my>=465 && my<=555))      //check garxa diyeko axis bhitra xa ki xna
            {
                help();
                break;
            }

            if((mx>=645 && mx<=910)&&(my>=605 && my<=695))      //check garxa diyeko axis bhitra xa ki xna
            {
                exit();
                break;
            }
        }
    }

}

void loading()
{
    int cx,cy,a,k=0;
    cx=getmaxx()/2;         //whole screen ko pixel divide by 2 in x axis
    cy=getmaxy()/2;
    setcolor(GREEN);
    readimagefile("loading.JPG", 0, 0, getmaxx(), getmaxy());//background image
    setbkcolor(RGB(237,244,240));
    settextstyle(1,0,1);
    outtextxy(634,525," Loading...........");       //display loading text
    rectangle(cx-180,cy+60,cx+180,cy+90);       //loading ko rectangle
    a=cx-180;
    for(int i=0; i<=12; i++)            //loop to display loading bhitra ko bar
    {
        setfillstyle(1,GREEN);
        delay(400);
        bar(a,cy+60,a+30,cy+90);
        a=a+30;

    }
    cleardevice();
    mainmenu();
}

int chksize(char s, char d)  //to check disk size
{
    if(s==d)        //char s ra char d le same data liyo bhane push pop nagarne
        {
            return 0;
        }
        else
        {
            int data1,data2;
            if(s=='s')
            {
                if(top1==-1)
                    {
                        return 0;
                    }
                else
                    {
                    data1=peg1[top1];
                    }
            }
            else if(s=='m')
            {
                if(top2==-1)
                    {
                        return 0;
                    }
                else
                    {
                data1=peg2[top2];
                    }

            }
            else if(s=='d')
            {
                if(top3==-1)
                    {
                        return 0;
                    }
                else
                    {
                data1=peg3[top3];
                    }
            }
            else
            {
                return 0;
            }

            if(d=='s')
            {
                if(top1==-1)
                {
                    data2=12;
                }
                else
                {
                    data2=peg1[top1];
                }
            }
            else if(d=='m')
            {
                if(top2==-1)
                {
                    data2=12;
                }
                else
                {
                    data2=peg2[top2];
                }
            }
            else if(d=='d')
            {
                if(top3==-1)
                {
                    data2=12;
                }
                else
                {
                    data2=peg3[top3];
                }
            }
            else
            {
                return 0;
            }
            if(data1<data2)
            {
                return 1;
            }
            else
            {
                setcolor(BLACK);
                outtextxy(550,200,"You can't place big disk over small disk");
                delay(1500);
                return 0;
            }
        }

    }

void gameover()
{
    readimagefile("gameover.JPG", 0, 0, getmaxx(), getmaxy());//background image
    //PlaySound("sadyoulose.wav", NULL, SND_ASYNC);

}

void youwin()
{
    readimagefile("youwin.JPG", 0, 0, getmaxx(), getmaxy());//background image
    //PlaySound("youwin.wav", NULL, SND_ASYNC);
}

void thankyou()
{
    readimagefile("thankyou.JPG", 0, 0, getmaxx(), getmaxy());//background image

}
void displaystart()
{
    readimagefile("whitetexture.JPG", 0, 0, getmaxx(), getmaxy());//background image
    setcolor(GREEN);
    setfillstyle(1,GREEN);
    bar(1375,50,1445,110);
    setfillstyle(1,RGB(62,97,154));
    settextstyle(1,0,1);
    //char numberstring is defined globally
    sprintf(numberstring, "%d", steps);     // conversion of int steps to char array numberstring
    sprintf(maxstepstring, "%d", maxsteps); // conversion of int maxsteps to char array maxstepstring
    //steps lai string ma convert gareko kinaki graphic window ma display garna string hunu parxa
    setcolor(BLACK);    //text ko color black gareko
    outtextxy(100,200,steptxt);     //char steptxt[10]="Steps =";
    outtextxy(200,200,numberstring);
    outtextxy(100,220,maxmovestring);
    outtextxy(330,220,maxstepstring);
    bar(100,700,1385,720);//tala ko line

    //kati wota disk user sanga input liyoo tyo term ma bar display garna

    bar(313-number*17-15,690,313+number*17+15,699 );  //1st peg horizontal
    bar(733-number*17-15,690,733+number*17+15,699 );  //2nd horizontal
    bar(1153-number*17-15,690,1153+number*17+15,699); //3rd horizontal
    bar(308,690-number*30-30,317,690);                //1st peg vertical
    bar(308+420,690-number*30-30,317+420,690);        //2nd peg vertical
    bar(308+420+420,690-number*30-30,317+420+420,690);//3rd peg vertical
    int disclen;
    for(int i=0; i<=top1; i++) //loop to display the source peg
    {
        disclen=25+(peg1[i]-1)*17;
        setfillstyle(1,peg1[i]);
        bar(313-disclen,660-i*30,313+disclen,690-i*30);

    }
    for(int i=0; i<=top2; i++) // loop to display the middle peg
    {
        disclen=25+(peg2[i]-1)*17;
        setfillstyle(1,peg2[i]);
        bar(733-disclen,660-i*30,733+disclen,690-i*30);
    }

    for (int i=0; i<=top3; i++) // loop to display the destination peg
    {
        disclen=25+(peg3[i]-1)*17;
        setfillstyle(1,peg3[i]);
        bar(1153-disclen,660-i*30,1153+disclen,690-i*30);
    }


}


void checkdata(char &source, char  &destination)
{
    if((mx1>=118 && mx1<=508)&&(my1>=360-cm && my1<=698-cm)) //-cm to correct mouse cursor in y axis
    {
        destination='s';
    }
    else if((mx1>=536 && mx1<=930) && (my1>=360-cm && my1<=698-cm))
    {
        destination='m';
    }
    else if((mx1>=956 && mx1<=1350) && (my1>=360-cm && my1<=698-cm))
    {
        destination='d';
    }
    else
    {
        destination='a';
    }

    if(my2>=360-cm && my2<=390-cm)
    {
        if(mx2>=289 && mx2<= 336)
        {
            source='s';
        }
        else if (mx2>=538  && mx2<=928 )
        {
            source='m';
        }
        else if (mx2>=958  && mx2<=1348 )
        {
            source='d';
        }
    }
    else  if(my2>390-cm && my2<=420-cm)
    {
        if(mx2>=272 && mx2<=353 )
        {
            source='s';
        }
        else if (mx2>=555  && mx2<=911 )
        {
            source='m';
        }
        else if (mx2>=975  && mx2<=1131 )
        {
            source='d';
        }
    }
    else  if(my2>420-cm && my2<=450-cm)
    {
        if(mx2>=255 && mx2<=370 )
        {
            source='s';
        }
        else if (mx2>= 572 && mx2<=894 )
        {
            source='m';
        }
        else if (mx2>=992  && mx2<=1314 )
        {
            source='d';
        }
    }
    else  if(my2>450-cm && my2<=480-cm)
    {
        if(mx2>=238 && mx2<=387 )
        {
            source='s';
        }
        else if (mx2>=589  && mx2<= 877)
        {
            source='m';
        }
        else if (mx2>=1009  && mx2<=1297 )
        {
            source='d';
        }
    }
    else  if(my2>480-cm && my2<=510-cm)
    {
        if(mx2>=221 && mx2<=404 )
        {
            source='s';
        }
        else if (mx2>=606  && mx2<=860 )
        {
            source='m';
        }
        else if (mx2>=1026  && mx2<=1280 )
        {
            source='d';
        }
    }
    else  if(my2>510-cm && my2<=540-cm)
    {
        if(mx2>=204 && mx2<=421 )
        {
            source='s';
        }
        else if (mx2>= 623 && mx2<=843 )
        {
            source='m';
        }
        else if (mx2>=1043  && mx2<=1263 )
        {
            source='d';
        }
    }
    else  if(my2>540-cm && my2<=570-cm)
    {
        if(mx2>=187 && mx2<=438 )
        {
            source='s';
        }
        else if (mx2>=640  && mx2<=826 )
        {
            source='m';
        }
        else if (mx2>=1060  && mx2<=1246 )
        {
            source='d';
        }
    }
    else  if(my2>570-cm && my2<=600-cm)
    {
        if(mx2>=170 && mx2<=455 )
        {
            source='s';
        }
        else if (mx2>=657  && mx2<=809 )
        {
            source='m';
        }
        else if (mx2>=1077  && mx2<=1229 )
        {
            source='d';
        }
    }
    else  if(my2>600-cm && my2<=630-cm)
    {
        if(mx2>=153 && mx2<=472 )
        {
            source='s';
        }
        else if (mx2>=674  && mx2<=792 )
        {
            source='m';
        }
        else if (mx2>=1094  && mx2<=1212 )
        {
            source='d';
        }
    }
    else  if(my2>630-cm && my2<=660-cm)
    {
        if(mx2>=136 && mx2<=489 )
        {
            source='s';
        }
        else if (mx2>= 691 && mx2<= 775)
        {
            source='m';
        }
        else if (mx2>=1111  && mx2<=1195 )
        {
            source='d';
        }
    }
    else  if(my2>660-cm && my2<=690-cm)
    {
        if(mx2>=119 && mx2<=506 )
        {
            source='s';
        }
        else if (mx2>=708  && mx2<= 758)
        {
            source='m';
        }
        else if (mx2>=1128  && mx2<=1178 )
        {
            source='d';
        }
    }
    else
    {
        source='a';
    }
}


void push(char peg,int data)
{
    if(peg=='s')
    {
        top1=top1+1;
        peg1[top1]=data;
    }
    else if(peg=='m')
    {
        top2=top2+1;
        peg2[top2]=data;
    }
    else if(peg=='d')
    {
        top3=top3+1;
        peg3[top3]=data;
    }
    else
    {
        cout<<"Error......";
        system("pause");
    }
}

int pop(char peg)
{
    int data;
    if(peg=='s')
    {
        data=peg1[top1];
        top1=top1-1;
        return data;
    }
    else if(peg=='m')
    {
        data=peg2[top2];
        top2=top2-1;
        return data;
    }
    else if(peg=='d')
    {
        data=peg3[top3];
        top3=top3-1;
        return data;
    }
    else
    {
        return 0;
    }
}


void gameclick()
{
    POINT cursorposition;       //point type ko cursor position banako
    int mx,my;
    char source, destination;
    do
    {
        delay(500);
        reg1=false;         //bool type global baniraxa mathi
        reg2=false;
        while(1)
        {
            //short is data type used to store short integer. ot is smaller than int
            SHORT leftMouseButtonState = GetAsyncKeyState(VK_LBUTTON);
            if (leftMouseButtonState & 0x8000)
            {
                GetCursorPos(&cursorposition);
                mx=cursorposition.x;
                my=cursorposition.y;
                setcolor(WHITE);
            //    cout<<mx<<"\t"<<my;
                circle(mx,my-16,5);
                mx2=mx;
                my2=my;
                reg1=true;
                break;
            }

        }
        delay(500);

        while(1)
        {
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                GetCursorPos(&cursorposition);
                mx=cursorposition.x;
                my=cursorposition.y;
                circle(mx,my-16,5);
                mx1=mx;
                my1=my;
                cout<<endl<<mx<<"\t"<<my<<endl;
                reg2=true;
                break;
            }

        }

        if(reg1==true && reg2==true)
        {
          //  setcolor(13);
          //  circle(508,698,5);
          //  system("pause");
            checkdata(source,destination); // gets the source and destination peg
            if(source!='a' && destination!='a') // checks if the input clicks are right or not
            {
                cout<<source<<"\t"<<destination<<endl;
                if(chksize(source,destination))
                {
                    int data=pop(source);
                    cout<<data<<endl;
                    push(destination,data);
                    steps++;
                    maxsteps--;
                 //   PlaySound("pop.wav", NULL, SND_ASYNC);
                }
                delay(100);
                displaystart();
            }
        }
        if (maxsteps==0)
        {
            break;
        }

    }
    while(top1>-1 || top2>-1); //2 bai condition false nabhayesama loop chalxa
    //if(GetAsyncKeyState())
    if(top1==-1 && top2==-1)
    {
        youwin();
    }
    else
    {
        gameover();
    }

}
void displaysolution()   //display ra displaysolution ko code 1 tai xa (bg image change garna ko lagia0
{
    int cx,cc;
    cx=getmaxx();
    cc=getmaxy();
    readimagefile("whitetexture.JPG", 0, 0, getmaxx(), getmaxy());//background image
    settextstyle(1,0,1);
    setfillstyle(1,RGB(62,97,154));
    bar(100,700,1385,720);//tala ko line
    bar(313-number*17-15,690,313+number*17+15,699 );//1st peg hori
    bar(733-number*17-15,690,733+number*17+15,699 );//2nd horizontal
    bar(1153-number*17-15,690,1153+number*17+15,699);//3rd horizontal
    bar(308,690-number*30-30,317,690);  //1st peg vertical
    bar(308+420,690-number*30-30,317+420,690);//2nd peg verticle
    bar(308+420+420,690-number*30-30,317+420+420,690);//3rd peg verticle
    int disclen;
    for(int i=0; i<=top1; i++) //loop to display the source peg
    {
        disclen=25+(peg1[i]-1)*17;
        setfillstyle(1,peg1[i]);
        bar(313-disclen,660-i*30,313+disclen,690-i*30);


    }
    for(int i=0; i<=top2; i++) // loop to display the middle peg
    {
        disclen=25+(peg2[i]-1)*17;
        setfillstyle(1,peg2[i]);
        bar(733-disclen,660-i*30,733+disclen,690-i*30);
    }

    for (int i=0; i<=top3; i++) // loop to display the destination peg
    {
        disclen=25+(peg3[i]-1)*17;
        setfillstyle(1,peg3[i]);
        bar(1153-disclen,660-i*30,1153+disclen,690-i*30);
    }
    delay(200);

}
void TOH(int n,char s,char m,char d)        //toh function using recursion
{
    if(n>0)
    {
        int data;
        TOH(n-1,s,d,m);
        // cout<<"\nMove a disk from "<<s<<" to "<<d<<endl;
        //  displaycon();
        displaysolution();
        data=pop(s);
        push(d,data);
        TOH(n-1,m,s,d);
    }
}

void start()            //main menu ko start thichesi yo call hunxa
{
    int n;
    char num[1];
    int x;
    x=getmaxx();
    cout<<x;       //char type ko array
    setbkcolor(WHITE);
    readimagefile("whitetexture.JPG", 0, 0, getmaxx(), getmaxy());//background image
    settextstyle(1,0,1);
    outtextxy(100,250,"Enter the number of disk:"); //window ma display gareko
    num[0]=getch(); //number character ko rup ma leko
    outtextxy(400,250,num);     //leko number yo position ma display garyo

    n=stoi(num);    //character to integer convert gareko       stoi bhaneko string to array
  //  PlaySound("startofgame.wav", NULL, SND_ASYNC);          // stop aagadi ko background music
    delay(1000);
    number=n;
    maxsteps=pow(2,n)-1;  //maxstep chai 2 ko power n-1 hunxa  (n+2)2 extra steps deko
    // user le deko number anusar peg1 ma push gareko
    for(int i=n; i>0; i--)      //peg 1 ma push gareko
    {
        push('s',i);
    }

    displaystart();
    gameclick();
}
void help()
{
    //cleardevice();
    top1=-1;
    top2=-1;
    top3=-1;
    setbkcolor(WHITE);
    readimagefile("whitetexture.JPG", 0, 0, getmaxx(), getmaxy());//background image
    settextstyle(1,0,1);
    int n;
    char num[3];
    outtextxy(100,100,"Enter the number of disk:"); //window ma display gareko
    num[0]=getch(); //number character ko rup ma leko
    outtextxy(400,100,num);
    num[1]=getch();
    outtextxy(405,100,num);
    n=stoi(num);    //character to integer convert gareko
    delay(700);
    number=n;
    for(int i=n; i>0; i--)     //push number of disk in first peg
    {
        push('s',i);
    }
    TOH(n,'s','m','d');  //Call toh function
    displaysolution();   //call displaysolution function
    delay(300);
    thankyou();
    getch();
    mainmenu();

}

void exit()
{
    readimagefile("thankyou.JPG", 0, 0, getmaxx(), getmaxy());//background image
    delay(1500);
    exit(0);


}

int main()
{
    int yn;
    initwindow(getmaxwidth(),getmaxheight(),"TOWER OF HANOI");  //naya graphic window banako

  //  PlaySound("yournamebgtheme.wav", NULL, SND_ASYNC);          //background music
  //  loading();
    mainmenu();
 //start();

    return 0;
}
