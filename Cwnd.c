#include<windows.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

//donot change this symbolic constant
#define interval 10

//the Time_delay symbolic constant is used to control the speed 
//of the simulation. default value is 100. to speed up the simulation, specify a value 
//lower than 100. similarly, a value higher than 100 will slow down
//the simulation
#define Time_delay 5

typedef struct node{
			int customer_number,enqueue_time;
			struct node *next,*previous;

		   } node;

typedef struct node* nodeptr;

nodeptr p,n,tmp,front,rear;

void enqueue(int,int);
int dequeue(void);

LRESULT APIENTRY event_handler(HWND,UINT,UINT,long);

WNDCLASS a;
RECT rcCurrent; 
int idTimer = -1; 
HDC hdc; 
HWND h;
MSG m;
static HFONT hfnt;
char str1[100],str2[100],str3[100],str4[100],str5[100],str6[100],
str7[100],jumbo[300],time_of_day[5]="A.M.",tmptod[5]="A.M",
arrival_tod[5],service_tod[5];

int current_time=1,customer_arrival_interval,
customer_service_interval,wait_time
,customer_arrival_time,customer_service_time=-1,customer_number=0,
is_customer_being_serviced=0,customers_in_queue=0,
maximum_wait_time=0,minutes=0,hours=8,tmph,tmpm,random_interval,
arrival_minute,arrival_hour,service_minute,service_hour,maximum_queue=0;

long moderator=0;

//HFONT EzCreateFont (HDC hdc, TCHAR * szFaceName, int iDeciPtHeight,
                    //int iDeciPtWidth, int iAttributes, BOOL fLogRes) ;

#define EZ_ATTR_BOLD          1
#define EZ_ATTR_ITALIC        2
#define EZ_ATTR_UNDERLINE     4
#define EZ_ATTR_STRIKEOUT     8

HFONT      hFont ;
     int        y, iPointSize ;
     LOGFONT    lf ;
     TCHAR      szBuffer [100] ;
     TEXTMETRIC tm ;


LRESULT APIENTRY WinMain(HINSTANCE e, HINSTANCE b, char *c, int d)
{
	
	a.hInstance=e;
	a.lpszClassName="adn";
	a.lpfnWndProc=event_handler;
	a.hbrBackground=GetStockObject(WHITE_BRUSH);

	RegisterClass(&a);

	tmpm=MessageBox(0,"Do you want to run the market simulation with a random arrival interval of 1 to 4 minutes? Select No for a random arrival interval of 1 to 3 minutes.","Deitel & Deitel's Market Simulation problem 12.15",MB_YESNO);

	if(tmpm==IDYES)
		random_interval=3;
	else
		random_interval=2;

	if(random_interval==3)
	h=CreateWindow("adn","Deitel & Deitel's Market Simulation problem 12.15 with 1 to 4 minute random arrival interval",WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,200,200,580,300,0,0,e,0);
	else
	h=CreateWindow("adn","Deitel & Deitel's Market Simulation problem 12.15 with 1 to 3 minute random arrival interval",WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,200,200,580,300,0,0,e,0);

	ShowWindow(h,1);

	srand( (unsigned)time( NULL ) );
	
	//determine customer_arrival_time randomly
	customer_arrival_interval=(rand()%random_interval)+1;
	customer_arrival_time=customer_arrival_interval + current_time;
	customer_number++;
	
	while(GetMessage(&m,0,0,0))
		DispatchMessage(&m);

	MessageBox(0,"This simulation was developed by Adnan Aziz Baloch, Roll No.04, BCS Section A Batch-I and presented to Mr.Rizwan Qureshi.","Deitel & Deitel's Market Simulation problem 12.15",0);

	return 0;
}

 
LRESULT APIENTRY event_handler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
    PAINTSTRUCT ps; 
    RECT rc; 
 
    switch (message) 
    { 
        case WM_CREATE: 
 
            hdc = GetDC(hwnd); 
			SetTimer(hwnd, idTimer = 1, interval, NULL); 
            return 0L; 
 
        case WM_DESTROY: 
            KillTimer(hwnd, 1); 
            PostQuitMessage(0); 
            return 0L;
 
        case WM_TIMER: 
			
			y = 30 ;

			if(current_time<720)
			moderator++;

		//////////////////////////////////////////////////////////
			GetClientRect(hwnd,&rcCurrent);
			
			FillRect(hdc, &rcCurrent, GetStockObject(WHITE_BRUSH));
			
		    iPointSize = 100;

			//hFont = EzCreateFont (hdc, TEXT ("Arial Unicode MS"), 
                                //iPointSize, 0, EZ_ATTR_BOLD | EZ_ATTR_ITALIC, TRUE) ;

			SetTextColor(hdc, RGB(255,0,0)/*GetSysColor(COLOR_WINDOWTEXT)*/);

			//GetObject (hFont, sizeof (LOGFONT), &lf) ;

			//SelectObject (hdc, hFont) ;
			//GetTextMetrics (hdc, &tm) ;
			
			if(current_time%2==0)
			{
				if(minutes<10)
				TextOut (hdc, 0, y, szBuffer, 
				wsprintf (szBuffer, 
				TEXT ("The time now is %i:0%i %hs"),hours,minutes,time_of_day)) ;
				else
					TextOut (hdc, 0, y, szBuffer, 
				wsprintf (szBuffer, 
				TEXT ("The time now is %i:%i %hs"),hours,minutes,time_of_day)) ;
			}
			else
			{
				if(minutes<10)
				TextOut (hdc, 0, y, szBuffer, 
				wsprintf (szBuffer, 
				TEXT ("The time now is %i 0%i %hs"),hours,minutes,time_of_day)) ;
				else
					TextOut (hdc, 0, y, szBuffer, 
				wsprintf (szBuffer, 
				TEXT ("The time now is %i %i %hs"),hours,minutes,time_of_day)) ;
			}


			//DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

		///////////////////////////////////////////////////
			//hFont = EzCreateFont (hdc, TEXT ("Arial Unicode MS"), 
                                //iPointSize, 0, EZ_ATTR_BOLD | EZ_ATTR_ITALIC, TRUE) ;
			//GetObject (hFont, sizeof (LOGFONT), &lf) ;

			//SelectObject (hdc, hFont) ;
			//GetTextMetrics (hdc, &tm) ;
			
			if(customer_arrival_time==current_time)
			{
				arrival_minute=minutes;
				arrival_hour=hours;
				strcpy(arrival_tod,time_of_day);
			}

			if(arrival_minute<10)
			TextOut (hdc, 0, y+=30, szBuffer, 
			wsprintf (szBuffer, 
              TEXT ("Customer number %i arrived at %i:0%i %hs"),customer_number-1,arrival_hour,arrival_minute,arrival_tod));
			else
				TextOut (hdc, 0, y+=30, szBuffer, 
			wsprintf (szBuffer, 
              TEXT ("Customer number %i arrived at %i:%i %hs"),customer_number-1,arrival_hour,arrival_minute,arrival_tod));
			

			//DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;
        /////////////////////////////////////////////////////
			
		//Has the customer been serviced yet?
		if(customer_service_time==current_time)
		{
			is_customer_being_serviced=0;
			if(dequeue())
			customers_in_queue--;
		}

		if(is_customer_being_serviced==0 && customers_in_queue>0)
		{
			is_customer_being_serviced=1;
			wait_time= current_time - (front->enqueue_time);
			if(wait_time>maximum_wait_time)
			maximum_wait_time=wait_time;
			//calculate random service time
			customer_service_interval=(rand()%3)+1;
			customer_service_time=customer_service_interval+current_time;
			service_minute=minutes;
			service_hour=hours;
			strcpy(service_tod,time_of_day);
		}

		//Has the customer arrived yet?
		if(customer_arrival_time==current_time)
		{
			enqueue(customer_number,current_time);
			customers_in_queue++;
			if(customers_in_queue>maximum_queue)
				maximum_queue=customers_in_queue;
			//is there a customer currently being serviced?
			if(is_customer_being_serviced==0)
			{
				is_customer_being_serviced=1;
				wait_time=0;
				//calculate random service time
				customer_service_interval=(rand()%3)+1;
				customer_service_time=customer_service_interval+current_time;
				service_minute=minutes;
				service_hour=hours;
				strcpy(service_tod,time_of_day);
			}

			//determine next customer_arrival_time randomly
			customer_arrival_interval=(rand()%random_interval)+1;
			customer_arrival_time=customer_arrival_interval+current_time;
			arrival_minute=minutes;
			arrival_hour=hours;
			strcpy(arrival_tod,time_of_day);
			customer_number++;
		}

		if(moderator%Time_delay==0 && current_time<720)
		{	current_time++;

			if(minutes<=60 && current_time<720)
			{
				if(minutes<60)
					minutes++;
				if(minutes==60)
				{
					minutes=0;

					if(hours<=12)
					{
						if(hours<12)
						hours++;
						else if(hours==12)
						hours=1;
					}

					if(hours==12 && minutes==0)
					{
						if(strcmp(time_of_day,"A.M.")==0)
							strcpy(time_of_day,"P.M.");
						else
							strcpy(time_of_day,"A.M.");
					}
					
				}
			}
		}

		
			///////////////////////////////////////////////////////

			//hFont = EzCreateFont (hdc, TEXT ("Arial Unicode MS"), 
                                //iPointSize, 0, EZ_ATTR_BOLD | EZ_ATTR_ITALIC, TRUE) ;

			//GetObject (hFont, sizeof (LOGFONT), &lf) ;

			//SelectObject (hdc, hFont) ;
			//GetTextMetrics (hdc, &tm) ;
			
			tmph=service_hour;
			tmpm=service_minute;
			strcpy(tmptod,service_tod);

			if( (tmpm+customer_service_interval) >=60)
			{
				for(;tmpm<customer_service_interval;tmpm++)
					if(tmpm==60)
					{
						tmpm=0;
						if(tmph==12 && tmpm==0)
						{
							if(strcmp(tmptod,"A.M.")==0)
								strcpy(tmptod,"P.M.");
							else
								strcpy(tmptod,"A.M.");
						}

						if(tmph==12)
							tmph=1;
						else
							tmph++;
					}
			}
			else
				tmpm+=customer_service_interval;

			if(tmpm<10)
			TextOut (hdc, 0, y+=30, szBuffer, 
			wsprintf (szBuffer, 
              TEXT ("and he is going to be serviced until %i:0%i %hs"),tmph,tmpm,tmptod));
			else
				TextOut (hdc, 0, y+=30, szBuffer, 
			wsprintf (szBuffer, 
              TEXT ("and he is going to be serviced until %i:%i %hs"),tmph,tmpm,tmptod));
			

			//DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

			//////////////////////////////////////////////////////////

			//hFont = EzCreateFont (hdc, TEXT ("Arial Unicode MS"), 
                                //iPointSize, 0, EZ_ATTR_BOLD | EZ_ATTR_ITALIC, TRUE) ;

			//GetObject (hFont, sizeof (LOGFONT), &lf) ;

			//SelectObject (hdc, hFont) ;
			//GetTextMetrics (hdc, &tm) ;
			
			tmph=arrival_hour;
			tmpm=arrival_minute;
			strcpy(tmptod,arrival_tod);

			if( (tmpm+customer_arrival_interval) >=60)
			{
				for(;tmpm<customer_arrival_interval;tmpm++)
					if(tmpm==60)
					{
						tmpm=0;
						if(tmph==12 && tmpm==0)
						{
							if(strcmp(tmptod,"A.M.")==0)
								strcpy(tmptod,"P.M.");
							else
								strcpy(tmptod,"A.M.");
						}

						if(tmph==12)
							tmph=1;
						else
							tmph++;
					}
			}
			else
				tmpm+=customer_arrival_interval;

			if(tmpm<10)
			TextOut (hdc, 0, y+=30, szBuffer, 
			wsprintf (szBuffer, 
              TEXT ("Next customer is expected at %i:0%i %hs"),tmph,tmpm,tmptod));
			else
				TextOut (hdc, 0, y+=30, szBuffer, 
			wsprintf (szBuffer, 
              TEXT ("Next customer is expected at %i:%i %hs"),tmph,tmpm,tmptod));

			//DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

			///////////////////////////////////////////////////////////
			
			//hFont = EzCreateFont (hdc, TEXT ("Arial Unicode MS"), 
                                //iPointSize, 0, EZ_ATTR_BOLD | EZ_ATTR_ITALIC, TRUE) ;

			//GetObject (hFont, sizeof (LOGFONT), &lf) ;

			//SelectObject (hdc, hFont) ;
			//GetTextMetrics (hdc, &tm) ;
			
			if(is_customer_being_serviced==0)
			TextOut (hdc, 0, y+=30, szBuffer, 
			wsprintf (szBuffer, 
              TEXT ("No customer is being serviced at this moment.")));

			//DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

			///////////////////////////////////////////////////////////

			//hFont = EzCreateFont (hdc, TEXT ("Arial Unicode MS"), 
                                //iPointSize, 0, EZ_ATTR_BOLD | EZ_ATTR_ITALIC, TRUE) ;

			//GetObject (hFont, sizeof (LOGFONT), &lf) ;

			//SelectObject (hdc, hFont) ;
			//GetTextMetrics (hdc, &tm) ;
			
			TextOut (hdc, 0, y+=30, szBuffer, 
			wsprintf (szBuffer, 
              TEXT ("The total number of customers in the queue is %i"),customers_in_queue));

			//DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;

			///////////////////////////////////////////////////////////

			//hFont = EzCreateFont (hdc, TEXT ("Arial Unicode MS"), 
                                //iPointSize, 0, EZ_ATTR_BOLD | EZ_ATTR_ITALIC, TRUE) ;

			//GetObject (hFont, sizeof (LOGFONT), &lf) ;

			//SelectObject (hdc, hFont) ;
			//GetTextMetrics (hdc, &tm) ;
			
			TextOut (hdc, 0, y+=30, szBuffer, 
			wsprintf (szBuffer, 
              TEXT ("The maximum wait time for a customer uptill now is %i minutes"),maximum_wait_time));

			//DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;
			//y += tm.tmHeight ;
			
			///////////////////////////////////////////////////////////

			//hFont = EzCreateFont (hdc, TEXT ("Arial Unicode MS"), 
                                //iPointSize, 0, EZ_ATTR_BOLD | EZ_ATTR_ITALIC, TRUE) ;

			//GetObject (hFont, sizeof (LOGFONT), &lf) ;

			//SelectObject (hdc, hFont) ;
			//GetTextMetrics (hdc, &tm) ;
			
			if(current_time==720)
			TextOut (hdc, 0, y+=30, szBuffer, 
			wsprintf (szBuffer, 
              TEXT ("The maximum number of customers that had to wait in queue was %i"),maximum_queue));

			//DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;
			
			///////////////////////////////////////////////////////////

			//hFont = EzCreateFont (hdc, TEXT ("Arial Unicode MS"), 
                                //iPointSize, 0, EZ_ATTR_BOLD | EZ_ATTR_ITALIC, TRUE) ;

			//GetObject (hFont, sizeof (LOGFONT), &lf) ;

			//SelectObject (hdc, hFont) ;
			//GetTextMetrics (hdc, &tm) ;
			
			if(current_time==720)
			TextOut (hdc, 0, y+=30, szBuffer, 
			wsprintf (szBuffer, 
              TEXT ("The simulation has ended.")));

			//DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT))) ;
			
			return 0L; 
 
    } 
    return DefWindowProc(hwnd, message, wParam, lParam); 
} 

void enqueue(int info,int wait)
{
	n=malloc(sizeof(node));
	n->customer_number=info;
	n->enqueue_time=wait;

	if(front==NULL && rear==NULL)
	{
		front=rear=n;
		front->next=rear;
		front->previous=rear;
		rear->next=front;
		rear->previous=front;
	}
	else if(front==rear)
	{
		rear=n;
		rear->next=front;
		rear->previous=front;
		front->next=rear;
		front->previous=rear;
	}
	else
	{
		tmp=rear;
		rear=n;
		rear->next=tmp;
		tmp->previous=rear;
		rear->previous=front;
		front->next=rear;
	}
}

int dequeue(void)
{
	p=front;

	if(front!=NULL && rear!=NULL)
	{
		if(front==rear)
		{
			tmp=front;
			front=NULL;
			rear=NULL;
			free(tmp);
		}
		else
		{
			tmp=front;
			front=front->previous;
			front->next=rear;
			rear->previous=front;
			free(tmp);
		}
	}
	else
	{
		return 0;
	}
	return 1;
}

/*HFONT EzCreateFont (HDC hdc, TCHAR * szFaceName, int iDeciPtHeight,
                    int iDeciPtWidth, int iAttributes, BOOL fLogRes)
{
     FLOAT      cxDpi, cyDpi ;
     HFONT      hFont ;
     LOGFONT    lf ;
     POINT      pt ;
     TEXTMETRIC tm ;
     
     SaveDC (hdc) ;
     
     //SetGraphicsMode (hdc, GM_ADVANCED) ;
     //ModifyWorldTransform (hdc, NULL, MWT_IDENTITY) ;
     //SetViewportOrgEx (hdc, 0, 0, NULL) ;
     //SetWindowOrgEx   (hdc, 0, 0, NULL) ;
     
     if (fLogRes)
     {
          cxDpi = (FLOAT) GetDeviceCaps (hdc, LOGPIXELSX) ;
          cyDpi = (FLOAT) GetDeviceCaps (hdc, LOGPIXELSY) ;
     }
     else
     {
          cxDpi = (FLOAT) (25.4 * GetDeviceCaps (hdc, HORZRES) /
                                        GetDeviceCaps (hdc, HORZSIZE)) ;
          
          cyDpi = (FLOAT) (25.4 * GetDeviceCaps (hdc, VERTRES) /
                                        GetDeviceCaps (hdc, VERTSIZE)) ;
     }
     
     pt.x = (int) (iDeciPtWidth  * cxDpi / 72) ;
     pt.y = (int) (iDeciPtHeight * cyDpi / 72) ;
     
     DPtoLP (hdc, &pt, 1) ;
     lf.lfHeight         = - (int) (fabs (pt.y) / 10.0 + 0.5) ;
     lf.lfWidth          = 0 ;
     lf.lfEscapement     = 0 ;
     lf.lfOrientation    = 0 ;
     lf.lfWeight         = iAttributes & EZ_ATTR_BOLD      ? 700 : 0 ;
     lf.lfItalic         = iAttributes & EZ_ATTR_ITALIC    ?   1 : 0 ;
     lf.lfUnderline      = iAttributes & EZ_ATTR_UNDERLINE ?   1 : 0 ;
     lf.lfStrikeOut      = iAttributes & EZ_ATTR_STRIKEOUT ?   1 : 0 ;
     lf.lfCharSet        = DEFAULT_CHARSET ;
     lf.lfOutPrecision   = 0 ;
     lf.lfClipPrecision  = 0 ;
     lf.lfQuality        = 0 ;
     lf.lfPitchAndFamily = 0 ;
     
     lstrcpy (lf.lfFaceName, szFaceName) ;
     
     hFont = CreateFontIndirect (&lf) ;
     
     if (iDeciPtWidth != 0)
     {
          hFont = (HFONT) SelectObject (hdc, hFont) ;
          
          GetTextMetrics (hdc, &tm) ;
          
          DeleteObject (SelectObject (hdc, hFont)) ;
          
          lf.lfWidth = (int) (tm.tmAveCharWidth *
                                        fabs (pt.x) / fabs (pt.y) + 0.5) ;
          
          hFont = CreateFontIndirect (&lf) ;
     }
     
     RestoreDC (hdc, -1) ;
     return hFont ;
}*/

