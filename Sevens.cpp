#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

void Colorset(DWORD color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//卡牌寬=19
//卡牌長=13

string spade[11]={
"         *         ",
"        ***        ",
"       *****       ",
"      *******      ",
"     *********     ",
"    ***********    ",
"   *************   ",
"  *****  *  *****  ",
"   ***  ***  ***   ",
"       *****       ",
"      *******      "};

string heart[11]={
"                   ",
"     ***   ***     ",
"    ***** *****    ",
"   *************   ",
"   *************   ",
"    ***********    ",
"      *******      ",
"       *****       ",
"        ***        ",
"         *         ",
"                   "};

string diamond[11]={
"         *         ",
"        ***        ",
"       *****       ",
"      *******      ",
"     *********     ",
"    ***********    ",
"     *********     ",
"      *******      ",
"       *****       ",
"        ***        ",
"         *         "};

string club[11]={
"                   ",
"        ***        ",
"       *****       ",
"      *******      ",
"   **  *****  **   ",
"  **** **********  ",
" ***************** ",
" *****   *   ***** ",
"  ***   ***   ***  ",
"       *****       ",
"      *******      "};

string xxx[11]={
"                   ",
"                   ",
"                   ",
"                   ",
"                   ",
"                   ",
"                   ",
"                   ",
"                   ",
"                   ",
"                   ",};

class sevens{
private:
    int playernum;
    int deck[52];
    vector<int> player1;
    vector<int> player2;
    vector<int> player3;
    vector<int> player4;
    vector<int> canplays;
    bool played[53];
    int smax,s7,smin,hmax,h7,hmin,cmax,c7,cmin,dmax,d7,dmin;
    int spade7;
    int sn,hn,dn,cn,now;
    int cardnum;
    int score1,score2,score3,score4;
public:
    sevens();
    void sevens_constructor(int);
    int find_spade7();
    void print_now();
    void print_now_card(int,int,int,int);
    void print_num(int,bool);
    void print_hand();
    void print_hand_forward(int,int);
    void print_card(int);
    int num_canplay();
    void print_canplay();
    bool canplay_check(int);
    bool pc_check(int);
    void play_card(int);
    void check_play(int);
    void throw_card(int,int);
    void player_throw(int);
    bool ai_play(int);
    int ai_check(int,vector<int>);
    int ai_throw(int);
    bool gameover();
    int whowin(int);
    int getplayernum();
    bool load();
    void save();
    unsigned int djb2hash(string s);
    bool check_save();
};

sevens::sevens(){
    srand(unsigned(time(0)));
    for(int i=0;i<52;i++)
        deck[i]=(i+1);
    random_shuffle(deck,deck+52);
}

void sevens::sevens_constructor(int n){
    playernum=n;
    if(n==2){
        for(int i=0;i<26;i++){
            player1.push_back(deck[i]);
            if(deck[i]==7) spade7=1;
        }
        for(int i=26;i<52;i++){
            player2.push_back(deck[i]);
            if(deck[i]==7) spade7=2;
        }
        cardnum=26;
        sort(player1.begin(),player1.end());
        sort(player2.begin(),player2.end());
    }
    else if(n==4){
        for(int i=0;i<13;i++){
            player1.push_back(deck[i]);
            if(deck[i]==7) spade7=1;
        }
        for(int i=13;i<26;i++){
            player2.push_back(deck[i]);
            if(deck[i]==7) spade7=2;
        }
        for(int i=26;i<39;i++){
            player3.push_back(deck[i]);
            if(deck[i]==7) spade7=3;
        }
        for(int i=39;i<52;i++){
            player4.push_back(deck[i]);
            if(deck[i]==7) spade7=4;
        }
        cardnum=13;
        sort(player1.begin(),player1.end());
        sort(player2.begin(),player2.end());
        sort(player3.begin(),player3.end());
        sort(player4.begin(),player4.end());
    }
    sn=0;hn=0,dn=0,cn=0;
    for(int i=0;i<cardnum;i++){
        //cout<<player1[i]<<" ";
        if(player1[i]<14) sn++;
        else if(player1[i]<27) hn++;
        else if(player1[i]<40) dn++;
        else cn++;
    }
    cout<<endl;
    for(int i=1;i<53;i++)
        played[i]=0;
    smax=0,s7=0,smin=0,hmax=0,h7=0,hmin=0,cmax=0,c7=0,cmin=0,dmax=0,d7=0,dmin=0;
    score1=0,score2=0,score3=0,score4=0;
}

int sevens::find_spade7(){
    s7=7;
    int a;
    played[7]=1;
    if(spade7==1){
        for(int i=0;i<player1.size();i++)
            if(player1[i]==7)
                a=i;
        player1.erase(player1.begin()+a);
        sn--;
    }
    else if(spade7==2){
        for(int i=0;i<player2.size();i++)
            if(player2[i]==7)
                a=i;
        player2.erase(player2.begin()+a);
    }
    else if(spade7==3){
        for(int i=0;i<player3.size();i++)
            if(player3[i]==7)
                a=i;
        player3.erase(player3.begin()+a);
    }
    else{
        for(int i=0;i<player1.size();i++)
            if(player4[i]==7)
                a=i;
        player4.erase(player4.begin()+a);
    }
    return (spade7%4);
}

void sevens::print_now(){
    cout<<"       Spade      ";Colorset(0X0C);cout<<"         Heart              Diamond          ";Colorset(0X0F);cout<<"    Club      "<<endl;
    cout<<endl;
    print_now_card(smax,hmax,dmax,cmax);
    cout<<endl;
    print_now_card(s7,h7,d7,c7);
    cout<<endl;
    print_now_card(smin,hmin,dmin,cmin);
    cout<<endl;
}

void sevens::print_now_card(int s,int h,int d,int c){

    for(int b=4;b>0;b--){
        Colorset(0xF0); cout<<"                   "; Colorset(0x0F); cout<<" ";
    }
    cout<<endl;

    Colorset(0xF0); print_num(s,1); Colorset(0X0F); cout<<" ";
    Colorset(0xFC); print_num(h,1); Colorset(0X0F); cout<<" ";
    Colorset(0xFC); print_num(d,1); Colorset(0X0F); cout<<" ";
    Colorset(0xF0); print_num(c,1); Colorset(0X0F); cout<<" ";
    cout<<endl;

    for(int i=0;i<11;i++){
        if(s==0){
            Colorset(0xF0); cout<<xxx[i]; Colorset(0x0F); cout<<" ";
        }
        else{
            Colorset(0xF0); cout<<spade[i]; Colorset(0x0F); cout<<" ";
        }
        if(h==0){
            Colorset(0xFC); cout<<xxx[i]; Colorset(0x0F); cout<<" ";
        }
        else{
            Colorset(0xFC); cout<<heart[i]; Colorset(0x0F); cout<<" ";
        }
        if(d==0){
            Colorset(0xFC); cout<<xxx[i];Colorset(0x0F);cout<<" ";
        }
        else{
            Colorset(0xFC); cout<<diamond[i];Colorset(0x0F);cout<<" ";
        }
        if(c==0){
            Colorset(0xF0); cout<<xxx[i];  Colorset(0x0F); cout<<" ";
        }
        else{
            Colorset(0xF0); cout<<club[i];  Colorset(0x0F); cout<<" ";
        }

        cout<<endl;
    }

    Colorset(0xF0); print_num(s,0); Colorset(0X0F); cout<<" ";
    Colorset(0xFC); print_num(h,0); Colorset(0X0F); cout<<" ";
    Colorset(0xFC); print_num(d,0); Colorset(0X0F); cout<<" ";
    Colorset(0xF0); print_num(c,0); Colorset(0X0F); cout<<" ";
    cout<<endl;

    for(int b=4;b>0;b--){
        Colorset(0xF0); cout<<"                   "; Colorset(0x0F); cout<<" ";
    }
    cout<<endl;
}

void sevens::print_num(int n, bool l){

    if(l==1){
        if(n==0) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("X")<<"               ";
        else if(n%13==1) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("A")<<"               ";
        else if(n%13==11) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("J")<<"               ";
        else if(n%13==12) cout<<"  "<<left <<setw(2)<<setfill(' ')<<("Q")<<"               ";
        else if(n%13==0) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("K")<<"               ";
        else{
            cout<<"  "<<left<<setw(2)<<setfill(' ')<<n%13<<"               ";
        }
    }
    else{
        if(n==0) cout<<"               "<<right<<setw(2)<<("X")<<"  ";
        else if(n%13==1) cout<<"               "<<right<<setw(2)<<("A")<<"  ";
        else if(n%13==11) cout<<"               "<<right<<setw(2)<<("J")<<"  ";
        else if(n%13==12) cout<<"               "<<right<<setw(2)<<("Q")<<"  ";
        else if(n%13==0) cout<<"               "<<right<<setw(2)<<("K")<<"  ";
        else
            cout<<"               "<<right<<setw(2)<<n%13<<"  ";
    }

}

void sevens::print_hand(){
    now=0;
   // cout<<sn<<" "<<hn<<" "<<dn<<" "<<cn<<endl<<endl;
    print_hand_forward(sn,1);
    print_hand_forward(hn,2);
    print_hand_forward(dn,3);
    print_hand_forward(cn,4);

}

void sevens::print_hand_forward(int n,int s){
    cout<<endl;
    for(int i=0;i<n;i++){
        Colorset(0xF0); cout<<"                   "; Colorset(0x0F); cout<<" ";
    }
    cout<<endl;
    for(int j=0;j<n;j++){
        if(s==1||s==4)
            Colorset(0xF0);
        else
            Colorset(0xFC);
        print_num(player1[now+j],1);
        Colorset(0X0F); cout<<" ";
    }
    cout<<endl;
    for(int i=0;i<11;i++){
        for(int j=0;j<n;j++){
            if(s==1){ //spade
                Colorset(0xF0);
                cout<<spade[i];
                Colorset(0x0F);
                cout<<" ";
            }
            else if(s==2){ //heart
                Colorset(0xFC);
                cout<<heart[i];
                Colorset(0x0F);
                cout<<" ";
            }
            else if(s==3){ //diamond
                Colorset(0xFC);
                cout<<diamond[i];
                Colorset(0x0F);
                cout<<" ";
            }
            else{ //club
                Colorset(0xF0);
                cout<<club[i];
                Colorset(0x0F);
                cout<<" ";
            }
        }
        cout<<endl;
    }
    for(int j=0;j<n;j++){
        if(s==1||s==4)
            Colorset(0xF0);
        else
            Colorset(0xFC);
        print_num(player1[now+j],0);
        Colorset(0X0F); cout<<" ";
    }
    cout<<endl;
    for(int i=0;i<n;i++){
        Colorset(0xF0); cout<<"                   "; Colorset(0x0F); cout<<" ";
    }
    cout<<endl;
    for(int i=0;i<n;i++,now++)
        cout<<"        "<<"("<<setw(2)<<setfill('0')<<now+1<<")"<<"        "; //5+4+8
    cout<<endl;
}

void sevens::print_card(int n){
    Colorset(0xF0); cout<<"                   "; Colorset(0x0F); cout<<" "; cout<<endl;
    int s;
    if(n<14) s=1;
    else if(n<27) s=2;
    else if(n<40) s=3;
    else s=4;
    if(s==1||s==4)
        Colorset(0xF0);
    else
        Colorset(0xFC);
    print_num(n,1);
    Colorset(0X0F); cout<<" "; cout<<endl;
    for(int i=0;i<11;i++){
        if(s==1){ //spade
            Colorset(0xF0);
            cout<<spade[i];
            Colorset(0x0F);
            cout<<" ";
        }
        else if(s==2){ //heart
            Colorset(0xFC);
            cout<<heart[i];
            Colorset(0x0F);
            cout<<" ";
        }
        else if(s==3){ //diamond
            Colorset(0xFC);
            cout<<diamond[i];
            Colorset(0x0F);
            cout<<" ";
        }
        else{ //club
            Colorset(0xF0);
            cout<<club[i];
            Colorset(0x0F);
            cout<<" ";
        }
    cout<<endl;
    }
    if(s==1||s==4)
        Colorset(0xF0);
    else
        Colorset(0xFC);
    print_num(n,0);
    Colorset(0X0F); cout<<" "; cout<<endl;
    Colorset(0xF0); cout<<"                   "; Colorset(0x0F); cout<<" "; cout<<endl;
}

int sevens::num_canplay(){
    canplays.clear();
    for(int i=0;i<cardnum;i++)
        if(canplay_check(player1[i])){
            canplays.push_back(i+1);
        }
    return canplays.size();
}

void sevens::print_canplay(){
    for(int i=0;i<canplays.size();i++)
        cout<<"("<<setw(2)<<setfill('0')<<canplays[i]<<")"<<" ";
    cout<<endl;
}

bool sevens::canplay_check(int x){
    //cout<<x<<" ";
    if(x%13==7)
        return 1;
    else if(x%13==1){
       // cout<<"p="<<played[x-1]<<" ";
        if(played[x+1])
            return 1;
        else
            return 0;
    }
    else if(x%13==0){
       // cout<<"p="<<played[x-1]<<" ";
        if(played[x-1])
            return 1;
        else
            return 0;
    }
    else {
        if(played[x-1]||played[x+1])
            return 1;
        else
            return 0;
    }
}

bool sevens::pc_check(int p){
    for(int i=0;i<canplays.size();i++){
        if(p==canplays[i]){
         //   cout<<"pc_check!"<<endl;
            return 1;
        }
    }
    //cout<<"pcfall"<<endl;
    return 0;
}

void sevens::play_card(int d){
    //cout<<"d="<<d<<endl;
    //cout<<"play start!"<<endl;
    check_play(player1[d-1]);
    played[player1[d-1]]=1;
    if(player1[d-1]<14) sn--;
    else if(player1[d-1]<27) hn--;
    else if(player1[d-1]<40) dn--;
    else cn--;
    cout<<endl<<"您已出牌！"<<endl;
    print_card(player1[d-1]);
    cout<<endl<<endl;
    //cout<<"change success!"<<endl;
    player1.erase(player1.begin()+(d-1));
    //cout<<"erase success!"<<endl;
    cardnum--;
}

void sevens::check_play(int n){
    //cout<<"check_start! n="<<n<<endl;
    if(n<14){
        if(n<7)
            smin=n;
        else
            smax=n;
    }
    else if(n<27){
        if(n%13==7)
            h7=7;
        else if(n%13==0)
            hmax=n;
        else if(n%13<7)
            hmin=n;
        else
            hmax=n;
    }
    else if(n<40){
        if(n%13==7)
            d7=7;
        else if(n%13==0)
            dmax=n;
        else if(n%13<7)
            dmin=n;
        else
            dmax=n;
    }
    else {
        if(n%13==7)
            c7=7;
        else if(n%13==0)
            cmax=n;
        else if(n%13<7)
            cmin=n;
        else
            cmax=n;
    }
}

bool sevens::gameover(){
    if(player1.size()==0&&player2.size()==0&&player3.size()==0&&player4.size()==0)
        return 1;
    else
        return 0;
}

void sevens::throw_card(int d,int p){
    if(p==1){
        int a=player1[d-1]%13;
        if(a==0) a=13;
        score1-=a;
    }
    else if(p==2){
        int a=player2[d]%13;
        if(a==0) a=13;
        score2-=a;
    }

    else if(p==3){
        int a=player3[d]%13;
        if(a==0) a=13;
        score3-=a;
    }
    else{
        int a=player4[d]%13;
        if(a==0) a=13;
        score4-=a;
    }
}

void sevens::player_throw(int d){
    int a=player1[d-1]%13;
    if(a==0) a=13;
    cout<<"您已蓋\牌！分數 -"<<a<<"分，目前為"<<score1<<"分"<<endl;
    if(player1[d-1]<14) sn--;
    else if(player1[d-1]<27) hn--;
    else if(player1[d-1]<40) dn--;
    else cn--;
    player1.erase(player1.begin()+(d-1));
    cardnum--;
}

bool sevens::ai_play(int p){
    vector<int> aiplay;
    if(p==2){
        for(int i=0;i<player2.size();i++){
            if(canplay_check(player2[i])){
                aiplay.push_back(i);
            }
        }
        if(aiplay.size()==0) return 0;
        else{
            int d=aiplay[ai_check(2,aiplay)];
            check_play(player2[d]);
            cout<<endl<<"電腦一已出牌："<<endl;
            print_card(player2[d]);
            played[player2[d]]=1;
            cout<<endl;
            player2.erase(player2.begin()+(d));
        }
    }
    else if(p==3){
        for(int i=0;i<player3.size();i++){
            if(canplay_check(player3[i])){
                aiplay.push_back(i);
            }
        }
        if(aiplay.size()==0) return 0;
        else{
            int d=aiplay[ai_check(3,aiplay)];
            check_play(player3[d]);
            cout<<endl<<"電腦二已出牌："<<endl;
            print_card(player3[d]);
            played[player3[d]]=1;
            cout<<endl;
            player3.erase(player3.begin()+(d));
        }
    }
    else {
       // cout<<"check1"<<endl;
        for(int i=0;i<player4.size();i++){
            if(canplay_check(player4[i])){
                aiplay.push_back(i);
            }
        }
       // cout<<"check2"<<endl;
       // cout<<aiplay.size()<<endl;
        if(aiplay.size()==0) return 0;
        else{
          //  cout<<"check3"<<endl;
            int d=aiplay[ai_check(4,aiplay)];
            check_play(player4[d]);
            cout<<endl<<"電腦三已出牌："<<endl;
            print_card(player4[d]);
            played[player4[d]]=1;
            cout<<endl;
            player4.erase(player4.begin()+(d));
        }
    }
    return 1;
}

int sevens::ai_check(int p,vector<int> aideck){
    int best,point=-100;
    if(p==2){
        for(int i=0;i<aideck.size();i++){
            int j=0;
            int x;
            if(aideck[i]<7){
                x=aideck[i]*(-3);
                for(j;player2[j]<7;j++){
                    x+=player2[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<13){
                x=aideck[i]*(-3);
                for(j;player2[j]<13;j++){
                    x+=player2[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<20){
                x=aideck[i]*(-3);
                for(j;player2[j]<20;j++){
                    x+=player2[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<26){
                x=aideck[i]*(-3);
                for(j;player2[j]<26;j++){
                    x+=player2[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<27){
                x=aideck[i]*(-3);
                for(j;player2[j]<27;j++){
                    x+=player2[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<33){
                x=aideck[i]*(-3);
                for(j;player2[j]<33;j++){
                    x+=player2[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<39){
                x=aideck[i]*(-3);
                for(j;player2[j]<39;j++){
                    x+=player2[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<40){
                x=aideck[i]*(-3);
                for(j;player2[j]<40;j++){
                    x+=player2[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<46){
                x=aideck[i]*(-3);
                for(j;player2[j]<46;j++){
                    x+=player2[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<52){
                x=aideck[i]*(-3);
                for(j;player2[j]<52;j++){
                    x+=player2[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
        }
        return best;
    }
    else if(p==3){
        for(int i=0;i<aideck.size();i++){
            int j=0;
            int x;
            if(aideck[i]<7){
                x=aideck[i]*(-3);
                for(j;player3[j]<7;j++){
                    x+=player3[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<13){
                x=aideck[i]*(-3);
                for(j;player3[j]<13;j++){
                    x+=player3[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<20){
                x=aideck[i]*(-3);
                for(j;player3[j]<20;j++){
                    x+=player3[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<26){
                x=aideck[i]*(-3);
                for(j;player3[j]<26;j++){
                    x+=player3[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<27){
                x=aideck[i]*(-3);
                for(j;player3[j]<27;j++){
                    x+=player3[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<33){
                x=aideck[i]*(-3);
                for(j;player3[j]<33;j++){
                    x+=player3[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<39){
                x=aideck[i]*(-3);
                for(j;player3[j]<39;j++){
                    x+=player3[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<40){
                x=aideck[i]*(-3);
                for(j;player3[j]<40;j++){
                    x+=player3[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<46){
                x=aideck[i]*(-3);
                for(j;player3[j]<46;j++){
                    x+=player3[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<52){
                x=aideck[i]*(-3);
                for(j;player3[j]<52;j++){
                    x+=player3[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
        }
        return best;
    }
    else{
        for(int i=0;i<aideck.size();i++){
            int j=0;
            int x;
            if(aideck[i]<7){
                x=aideck[i]*(-3);
                for(j;player4[j]<7;j++){
                    x+=player4[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<13){
                x=aideck[i]*(-3);
                for(j;player4[j]<13;j++){
                    x+=player4[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<20){
                x=aideck[i]*(-3);
                for(j;player4[j]<20;j++){
                    x+=player4[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<26){
                x=aideck[i]*(-3);
                for(j;player4[j]<26;j++){
                    x+=player4[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<27){
                x=aideck[i]*(-3);
                for(j;player4[j]<27;j++){
                    x+=player4[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<33){
                x=aideck[i]*(-3);
                for(j;player4[j]<33;j++){
                    x+=player4[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<39){
                x=aideck[i]*(-3);
                for(j;player4[j]<39;j++){
                    x+=player4[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<40){
                x=aideck[i]*(-3);
                for(j;player4[j]<40;j++){
                    x+=player4[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<46){
                x=aideck[i]*(-3);
                for(j;player4[j]<46;j++){
                    x+=player4[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
            else if(aideck[i]<52){
                x=aideck[i]*(-3);
                for(j;player4[j]<52;j++){
                    x+=player4[j];
                }
                if(x>point){
                    point=x;
                    best=i;
                }
            }
        }
        return best;
    }
}

int sevens::ai_throw(int p){
    int d,b;
    if(p==2){
        b=ai_check(2,player2);
        d=player2[b];
        throw_card(d,2);
        player2.erase(player2.begin()+b);
    }
    else if(p==3){
        b=ai_check(3,player3);
        d=player3[b];
        throw_card(d,3);
        player3.erase(player3.begin()+b);
    }
    else {
        b=ai_check(4,player4);
        d=player4[b];
        throw_card(d,4);
        player4.erase(player4.begin()+b);
    }
    return d;
}

int sevens::whowin(int a){
    int m=-1000;
    int win=0;
    cout<<"玩家(你)扣分為："<<score1<<endl;
    if(score1>m){
        win=1;
        m=score1;
    }
    cout<<"電腦一扣分為："<<score2<<endl;
    if(score2>m){
        win=2;
        m=score2;
    }
    else if(score2==m){
        win=5;
    }
    if(a==4){
        cout<<"電腦二扣分為："<<score3<<endl;
        if(score3>m)
            win=3;
        else if(score3==m){
            if(win==1)
                win=6;
            if(win==2)
                win=7;
            if(win==5)
                win=8;
        }
        cout<<"電腦三扣分為："<<score4<<endl;
        if(score4>m){
            win=4;
        }
        else if(score4==m){
            if(win==1)
                win=9;
            if(win==2)
                win=10;
            if(win==3)
                win=11;
            if(win==5)
                win=12;
            if(win==6)
                win=13;
            if(win==7)
                win=14;
            if(win==8)
                win=15;
        }
    }
    return win;
}

int sevens::getplayernum(){
    return playernum;
}

bool sevens::load(){
    //cout<<"start opening"<<endl;
    fstream loading;
    loading.open("save.dat", ios::in);
    //cout<<"start load"<<endl;
    int num;
    int p1size,p2size,p3size,p4size;
    loading>>playernum>>smax>>s7>>smin>>hmax>>h7>>hmin>>cmax>>c7>>cmin>>dmax>>d7>>dmin;
    loading>>cardnum>>sn>>hn>>dn>>cn;
    loading>>p1size>>p2size>>p3size>>p4size;
    for(int i=0;i<p1size;i++){
        int x;
        loading>>x;
        player1.push_back(x);
    }
    for(int i=0;i<p2size;i++){
        int x;
        loading>>x;
        player2.push_back(x);
    }
    for(int i=0;i<p3size;i++){
        int x;
        loading>>x;
        player3.push_back(x);
    }
    for(int i=0;i<p4size;i++){
        int x;
        loading>>x;
        player4.push_back(x);
    }
    loading>>score1>>score2>>score3>>score4;
    for(int i=1;i<53;i++)
        loading>>played[i];
    //cout<<"load over"<<endl;
    if(!check_save()){
        cout<<"偵測到檔案被竄改，檔案已毀損，請重新開始遊戲！"<<endl;
        return 0;
    }
    else
        return 1;
}

void sevens::save(){
    fstream saving,hashcheck;
    saving.open("save.dat", ios::out);
    hashcheck.open("game.dat", ios::out);
    if(!saving||!hashcheck){
        cout<<"存檔已毀損，請刪除所有檔案並重新解壓縮"<<endl;
        exit(-1);
    }
    int tablevalue=playernum+smax+s7+smin+hmax+h7+hmin+cmax+c7+cmin+dmax+d7+dmin;
    int cardvalue=cardnum+sn+hn+dn+cn;
    int player1value=0,player2value=0,player3value=0,player4value=0;
    int scorevalue=score1+score2*2+score3*3+score4*4;
    int playcardvalue=0;
    saving<<playernum<<" "<<smax<<" "<<s7<<" "<<smin<<" "<<hmax<<" "<<h7<<" "<<hmin<<" "<<cmax<<" "<<c7<<" "<<cmin<<" "<<dmax<<" "<<d7<<" "<<dmin<<endl;
    saving<<cardnum<<" "<<sn<<" "<<hn<<" "<<dn<<" "<<cn<<endl;
    saving<<player1.size()<<" "<<player2.size()<<" "<<player3.size()<<" "<<player4.size()<<endl;
    for(int i=0;i<player1.size();i++){
        player1value+=player1[i];
        saving<<player1[i]<<" ";
    }
    saving<<endl;
    for(int i=0;i<player2.size();i++){
        player2value+=player2[i];
        saving<<player2[i]<<" ";
    }
    saving<<endl;
    for(int i=0;i<player3.size();i++){
        player3value+=player3[i];
        saving<<player3[i]<<" ";
    }
    saving<<endl;
    for(int i=0;i<player4.size();i++){
        player4value+=player4[i];
        saving<<player4[i]<<" ";
    }
    saving<<endl;
    saving<<score1<<" "<<score2<<" "<<score3<<" "<<score4<<endl;
    for(int i=1;i<53;i++){
        playcardvalue+=played[i];
        saving<<played[i]<<" ";
    }
    saving<<endl;
    stringstream ss1;
    ss1<<tablevalue; string tablevalues; ss1>>tablevalues;
    stringstream ss2;
    ss2<<cardvalue; string cardvalues; ss2>>cardvalues;
    stringstream ss3;
    ss3<<player1value; string player1values; ss3>>player1values;
    stringstream ss4;
    ss4<<player2value; string player2values; ss4>>player2values;
    stringstream ss5;
    ss5<<player3value; string player3values; ss5>>player3values;
    stringstream ss6;
    ss6<<player4value; string player4values; ss6>>player4values;
    stringstream ss7;
    ss7<<scorevalue; string scorevalues; ss7>>scorevalues;
    stringstream ss8;
    ss8<<playcardvalue; string playcardvalues; ss8>>playcardvalues;
    //cout<<tablevalues<<" "<<cardvalues<<" "<<player1values<<" "<<player4values<<" "<<scorevalues<<" "<<playcardvalues<<endl;
    //system("pause");
    hashcheck<<djb2hash(tablevalues)<<" "<<djb2hash(cardvalues)<<endl;
    hashcheck<<djb2hash(player1values)<<" "<<djb2hash(player2values)<<" "<<djb2hash(player3values)<<" "<<djb2hash(player4values)<<endl;
    hashcheck<<djb2hash(scorevalues)<<" "<<djb2hash(playcardvalues)<<endl;
    cout<<"遊戲已存檔！程式將自動結束！"<<endl;
}

bool sevens::check_save(){
    fstream loading,hashcheck;
    loading.open("save.dat", ios::in);
    hashcheck.open("game.dat", ios::in);
    //cout<<"start check"<<endl;
    if(!hashcheck)
        return 0;
    string original[8]={};
    //cout<<"LONG LONG INT"<<endl;
    long long int hashvalue[8];
    int s;
    for(int i=0;i<8;i++){
        hashcheck>>hashvalue[i];
        //cout<<hashvalue[i]<<endl;
    }
    //cout<<"read hash over"<<endl;
    int tablevalue=playernum+smax+s7+smin+hmax+h7+hmin+cmax+c7+cmin+dmax+d7+dmin;
    //cout<<"t="<<tablevalue<<endl;
    int cardvalue=cardnum+sn+hn+dn+cn;
    int player1value=0,player2value=0,player3value=0,player4value=0;
    int scorevalue=score1+score2*2+score3*3+score4*4;
    int playcardvalue=0;
    for(int i=0;i<player1.size();i++)
        player1value+=player1[i];
    for(int i=0;i<player2.size();i++)
        player2value+=player2[i];
    for(int i=0;i<player3.size();i++)
        player3value+=player3[i];
    for(int i=0;i<player4.size();i++)
        player4value+=player4[i];
    for(int i=1;i<53;i++)
        playcardvalue+=played[i];

    stringstream ss1;
    ss1<<tablevalue; string tablevalues; ss1>>tablevalues;
    stringstream ss2;
    ss2<<cardvalue; string cardvalues; ss2>>cardvalues;
    stringstream ss3;
    ss3<<player1value; string player1values; ss3>>player1values;
    stringstream ss4;
    ss4<<player2value; string player2values; ss4>>player2values;
    stringstream ss5;
    ss5<<player3value; string player3values; ss5>>player3values;
    stringstream ss6;
    ss6<<player4value; string player4values; ss6>>player4values;
    stringstream ss7;
    ss7<<scorevalue; string scorevalues; ss7>>scorevalues;
    stringstream ss8;
    ss8<<playcardvalue; string playcardvalues; ss8>>playcardvalues;

    original[0]=tablevalues;
    original[1]=cardvalues;
    original[2]=player1values;
    original[3]=player2values;
    original[4]=player3values;
    original[5]=player4values;
    original[6]=scorevalues;
    original[7]=playcardvalues;
    for(int i=0;i<8;i++){
    //    cout<<i<<"-th original:"<<original[i]<<endl;
    //    cout<<i<<"="<<djb2hash(original[i])<<endl;
    //    cout<<"hash = "<<hashvalue[i]<<endl;
        if(hashvalue[i]!=djb2hash(original[i])){
        //    cout<<"Problem is "<<i<<"-th"<<endl;
            return 0;
        }
    }
    return 1;
}

unsigned int sevens::djb2hash(string s){
    unsigned int n=5381;
    for (int i=0;s[i];i++)
        //n*33+s[i]
        n=((n<<5)+n)+s[i];
    return (n&0x7FFFFFFF);
}

bool havesave(){
    fstream loading, hashcheck;
    loading.open("save.dat", ios::in);
    hashcheck.open("game.dat", ios::in);
    if(!loading||!hashcheck){
        return 0;
    }
    else{
        cout<<"檢查到上次有存檔記錄，請問是否讀取存檔？(Y/N)"<<endl;
        loading.close();
        hashcheck.close();
        return 1;
    }
}

int main(){
    COORD Sz;
    Sz.X=500; Sz.Y=1000;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),Sz);
    int a=1,ifload=0;
    char ans='A';
    cout<<"排七 Sevens!!!"<<endl;
    system("pause");
    Colorset(0x06);
    cout<<"注意事項："<<endl;
    cout<<"有設定視窗大小，所以請勿將視窗最大化。"<<endl;
    cout<<"在非最大化的情況下，可以拉動橫向與直向卷軸來查看所有畫面"<<endl;
    Colorset(0x0C);
    cout<<"★若是按到最大化，請重新開啟程式★"<<endl;
    Colorset(0x0F);
    system("pause");
    if(havesave())
        ifload=1;
    while(a!=0){
        sevens sss777;
        int p;
        if(ifload){
            while(ans!='Y'&&ans!='N'){
                cout<<"請輸入 Y or N "<<endl;
                cin>>ans;
            }
        }
        if(ans=='Y'){
     //       cout<<"load start!"<<endl;
            if(!sss777.load()){
                ans='N';
            }
            else{
                p=1;
                a=sss777.getplayernum();
            }
        }
        if(ans!='Y'){
            while(a!=2&&a!=4){
                cout<<"請輸入玩家數(2or4)，輸入0則結束程式"<<endl;
                cin>>a;
                if(a==0)
                    break;
                else if(a!=2&&a!=4){
                    cout<<"請輸入正確的玩家人數"<<endl;
                    continue;
                }
            }
            if(a==4)
                cout<<"本場遊戲順序為：玩家(你)→電腦一→電腦二→電腦三→玩家(你)"<<endl<<endl;
                Sleep(1500);
            sss777.sevens_constructor(a);

            cout<<"黑桃七優先出牌！"<<endl<<endl<<"擁有黑桃七的玩家為：";
            p=sss777.find_spade7();
            if(p==1) cout<<"玩家(你)"<<endl<<endl<<"你已出完黑桃七！"<<endl;
            else if(p==2) cout<<"電腦(一)"<<endl<<endl<<"電腦一已出黑桃七！"<<endl;
            else if(p==3) cout<<"電腦(二)"<<endl<<endl<<"電腦二已出黑桃七！"<<endl;
            else if(p==0) cout<<"電腦(三)"<<endl<<endl<<"電腦三已出黑桃七！"<<endl;
            sss777.print_card(7);
            p++; p%=a;
            if(a==2&&p==0) p=2;
        }
        while(!sss777.gameover()){
            if(p==1){
                cout<<endl<<"以下為牌組目前狀況"<<endl;
                int pc;
                Sleep(1500);
                cout<<"輪到你了！"<<endl<<endl;
                sss777.print_now();
                cout<<"以下為您的手牌"<<endl;
                Sleep(1500);
                sss777.print_hand();
                if(sss777.num_canplay()){
                    cout<<"您可出的牌有：";
                    sss777.print_canplay();
                    cout<<"您要出的牌是？(請輸入1,2,3...)"<<endl;
                    cout<<"若想結束遊戲並存檔，請輸入0"<<endl;
                    cin>>pc;
                    if(pc==0){
                        sss777.save();
                        return 0;
                    }
                    while(!sss777.pc_check(pc)){
                        cout<<"請輸入能出的手牌：";
                        sss777.print_canplay();
                        cout<<endl;
                        cin>>pc;
                    }
                    //cout<<"play!";
                    sss777.play_card(pc);
                }
                else{
                    int d;
                    cout<<endl<<"您沒有牌可出了，請選擇要蓋\的牌："<<endl;
                    cout<<"若想結束遊戲並存檔，請輸入0"<<endl;
                    cin>>d;
                    if(d==0){
                        sss777.save();
                        return 0;
                    }
                    sss777.throw_card(d,1);
                    sss777.player_throw(d);
                }
                p++;
                //cout<<"p="<<p<<endl;
            }
            else if(p==2){//電腦回合
                //cout<<"電腦一的回合"<<endl;
                Sleep(1500);
                if(!sss777.ai_play(2)){
                    sss777.ai_throw(2);
                    cout<<endl<<"電腦一已蓋\牌"<<endl;
                }
                p++;
            }
            else if(p==3){//電腦回合
               // cout<<"電腦二的回合"<<endl;
                Sleep(1500);
                if(!sss777.ai_play(3)){
                    //cout<<"check4"<<endl;
                    sss777.ai_throw(3);
                    cout<<endl<<"電腦二已蓋\牌"<<endl;
                }
                p++;
            }
            else {//電腦回合
                //cout<<"電腦三的回合"<<endl;
                Sleep(1500);
                if(!sss777.ai_play(4)){
                    sss777.ai_throw(4);
                    cout<<endl<<"電腦三已蓋\牌"<<endl;
                }
                p++;
            }
            p%=a;
            //cout<<"p%a="<<p<<endl;
            if(a==2&&p==0) p=2;
        }
        cout<<"遊戲結束"<<endl;
        int w=sss777.whowin(a);
        cout<<endl; Colorset(0X0C);
        if(w==1) cout<<"玩家(你)獲勝！"<<endl;
        else if(w==2) cout<<"電腦一獲勝！"<<endl;
        else if(w==3) cout<<"電腦二獲勝！"<<endl;
        else if(w==4) cout<<"電腦三獲勝！"<<endl;
        else if(w==5) cout<<"玩家(你)和電腦一同分！"<<endl;
        else if(w==6) cout<<"玩家(你)和電腦二同分！"<<endl;
        else if(w==7) cout<<"電腦一和電腦二同分！"<<endl;
        else if(w==8) cout<<"玩家(你)和電腦一和電腦二同分！"<<endl;
        else if(w==9) cout<<"玩家(你)和電腦三同分！"<<endl;
        else if(w==10) cout<<"電腦一和電腦三同分！"<<endl;
        else if(w==11) cout<<"電腦二和電腦三同分！"<<endl;
        else if(w==12) cout<<"玩家(你)和電腦一和電腦三同分！"<<endl;
        else if(w==13) cout<<"玩家(你)和電腦二和電腦三同分！"<<endl;
        else if(w==14) cout<<"電腦一和電腦二和電腦三同分！"<<endl;
        else if(w==15) cout<<"玩家(你)和電腦一和電腦二和電腦三同分！"<<endl;
        cout<<endl<<endl;
        Colorset(0X0F);
        system("pause");
        cout<<"已開始新的一局遊戲"<<endl;
    }
}
