#include<bits/stdc++.h>
#include<windows.h>

using namespace std;

void Colorset(DWORD color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//卡牌寬=19
//卡牌長=13

string Number[14] = {"  "," A"," 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9","10"," J"," Q"," K"};

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

int operator+ (pair<int,int> a,pair<int,int> b) //overload + 計算分數
{
	int total=0;
	if(a.first%2==1){
		if(a.second==1) total+=20;
		else if(a.second>=9) total+=10;
		else total+=a.second;
	}
	else if(a.first==0&&a.second==1) total+=10;
	if(b.first%2==1){
		if(b.second==1) total+=20;
		else if(b.second>=9) total+=10;
		else total+=b.second;
	}
	else if(b.first==0&&b.second==1) total+=10;
	return total;
}

bool cmp_first(pair<int,int> a,pair<int,int> b){
    if(a.first==b.first) return a.second<b.second;
    else return a.first<b.first;
}

bool cmp_second(pair<int,int> a,pair<int,int> b){
    return a.second>b.second;
}

bool cmp_rule(pair<int,int> a,pair<int,int> b){
    if(a.first%2!=b.first%2){
        if(a.first) return 1;
        else return 0;
    }
    else{
        if(a.first){
            if(a.second==1) return 1;
            else if(a.second>=9){
                if(b.second==1)
                    return 1;
                else
                    return 0;
            }
            else return 0;
        }
        else{
            if(a.second==1&&b.second==1){
                if(a.first==0)
                    return 1;
                else return 0;
            }
            else
                return a.second<b.second;
        }
    }
}

class Card{
private:
    map<string,int> suit;
    vector<pair<int,int> > player[4];
    vector<pair<int,int> > table;
    vector<pair<int,int> > deck;
    vector<pair<int,int> > score;
    vector<pair<int,int> > mem;
    int p=-1;
    int save_ins=0;
public:
    Card();
    bool card_check(int);
    void input(int);
    bool play1(int,pair<int,int>);
    bool play2(int,pair<int,int>);
    void turn(int,pair<int,int>);
    bool load();
    void save();
    unsigned int djb2hash(string s);
    bool check_save();
    bool gameover();
    void games();

friend ostream &operator<< (ostream &output,Card &c);
};

Card::Card(){
    for(int i=0;i<4;i++)
        player[i].clear();
    table.clear();
    deck.clear();
    score.clear();
    suit["spade"]=0;
    suit["heart"]=1;
    suit["club"]=2;
    suit["diamond"]=3;
    srand(unsigned(time(0)));
    cout<<"請輸入玩家個數(2~4):";
    cin>>p;
    while(p<2||p>4){
        cout<<"錯誤輸入!請輸入玩家個數(2~4):"<<endl;
        cin>>p;
    }
    vector<int> poke;
    for(int i=0;i<52;i++)
        poke.push_back(i);
    random_shuffle(poke.begin(),poke.end());
    int z=0;
    for(int i=0;i<p;i++){
        for(int j=0;j<24/p;j++){
            player[i].push_back(make_pair(poke[z]/13,poke[z]%13+1));
            z++;
        }
    }
    for(int i=0;i<p;i++)
        sort(player[i].begin(),player[i].end(),cmp_first);
    for(int i=0;i<4;i++){
        table.push_back(make_pair(poke[z]/13,poke[z]%13+1));
        z++;
    }
    for(int i=0;i<24;i++){
        deck.push_back(make_pair(poke[z]/13,poke[z]%13+1));
        z++;
    }
    for(int i=0;i<p;i++)
        score.push_back(make_pair(i,0));
}


bool Card::card_check(int pi){
    mem.clear();
    vector<pair<int,int> > temp,num;
    for(int i=0;i<player[pi].size();i++){
        for(int j=0;j<table.size();j++){
            if(player[pi][i].second<10)
                if(player[pi][i].second+table[j].second==10)
                    temp.push_back(make_pair(i,j));
            else
                if(player[pi][i].second==table[j].second)
                    temp.push_back(make_pair(i,j));
        }
    }

    for(int i=0;i<temp.size();i++)
        num.push_back(make_pair(i,player[pi][temp[i].first]+table[temp[i].second]));
    sort(num.begin(),num.end(),cmp_second);
    for(int i=0;i<num.size();i++){
        if(pi==0&&num[i].second>0)
            mem.push_back(temp[num[i].first]);
        else
            mem.push_back(temp[num[i].first]);
    }
    if(mem.empty())
        return 0;
    else
        return 1;
}

bool Card::play1(int pi,pair<int,int> c){
    bool check=0;
    int z=-1;
    for(int i=0;i<mem.size();i++){
        if(player[pi][mem[i].first].first==c.first&&player[pi][mem[i].first].second==c.second){
            check=1;
            z=i;
            break;
        }
    }
    if(check){
        score[pi].second+=player[pi][mem[z].first]+table[mem[z].second];
        player[pi].erase(player[pi].begin()+mem[z].first);
        table.erase(table.begin()+mem[z].second);
    }
    return check;
}

bool Card::play2(int pc,pair<int,int> c){
    bool check=0;
    int z=-1;
    for(int i=0;i<player[pc].size();i++){
        if(player[pc][i].first==c.first&&player[pc][i].second==c.second){
            check=1;
            z=i;
            break;
        }
    }
    if(check){
        player[pc].erase(player[pc].begin()+z);
        table.push_back(c);
    }
    return check;
}

void Card::turn(int pc,pair<int,int> c){
    for(int i=0;i<table.size();i++){
        if(c.second<10){
            if(c.second+table[i].second==10){
                score[pc].second+=c+table[i];
                table.erase(table.begin()+i);
                return;
            }
        }
        else{
            if(c.second==table[i].second){
                score[pc].second+=c+table[i];
                table.erase(table.begin()+i);
                return;
            }
        }
    }
    table.push_back(c);
}

void Card::input(int pi){
    if(pi==0){
        string s;
        int pc;
        if(card_check(0)){
            cout<<endl;
            cout<<"您要出的牌是？請輸入花色(spade,heart,club,diamond)"<<endl;
            while(cin>>s){
            if(suit.count(s)){
                if(cout<<"再輸入數字(1~13)"&&cin>>pc &&pc>0&&pc<=13&&play1(0,make_pair(suit[s],pc))){
                    turn(0,deck[0]);
                    deck.erase(deck.begin());
                    break;
                }
            }
            else
                cout<<"請重新輸入!"<<endl;
            }
        }
        else{
            cout<<endl;
            cout<<"您要出的牌是？(請輸入花色(spade,heart,club,diamond)"<<endl;
            while(cin>>s){
            if(suit.count(s)){
                if(cout<<"再輸入數字(1~13)"&&cin>>pc &&pc>0&&pc<=13&&play2(0,make_pair(suit[s],pc))){
                    turn(0,deck[0]);
                    deck.erase(deck.begin());
                    break;
                }
            }
            else
                cout<<"請重新輸入!"<<endl;
            }
        }
    }
    else{
        if(card_check(pi)){
            play1(pi,player[pi][mem[0].first]);
            turn(pi,deck[0]);
            deck.erase(deck.begin());
        }
        else{
            vector<pair<int,int> > temp;
            for(int i=0;i<player[pi].size();i++)
                temp.push_back(player[pi][i]);
            sort(temp.begin(),temp.end(),cmp_rule);
            play2(pi,temp[temp.size()-1]);
            turn(pi,deck[0]);
            deck.erase(deck.begin());
        }
    }
}

void Card::games(){
    system("cls");
        cout << *this;
        for(int i=0;i<p;i++){
            input(i);
        }
}

bool Card::gameover(){
    for(int i=0;i<p;i++){
        if(!player[i].empty())
            return 1;
    }
    sort(score.begin(),score.end(),cmp_second);
    cout<<endl<<endl;
    cout<<"遊戲已結束，以下為成績"<<endl;
    for(int i=0;i<p;i++){
        if(score[i].first==0)
            cout<<"玩家  "<<"分數為"<<score[i].second<<endl;
        else
            cout<<"電腦"<<score[i].first<<"分數為"<<score[i].second<<endl;
    }
    return 0;
}


ostream &operator<< (ostream &output, Card &c){
    Colorset(0x0F);
    int pc=0;
    int sizee=c.table.size();
    int a=0,b=0;
    cout<<endl;
    output<<"目前牌桌狀況:"<<endl;
    for(int i=0;i<sizee;i++){
        Colorset(0xF0); cout<<"                   "; Colorset(0x0F); cout<<" ";
    }
    cout<<endl;
    for(int i=0;i<sizee;i++){
        if(c.table[i].first==0||c.table[i].first==2)
            Colorset(0xF0);
        else
            Colorset(0xFC);
        if(c.table[i].second==1) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("A")<<"               ";
        else if(c.table[i].second==11) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("J")<<"               ";
        else if(c.table[i].second==12) cout<<"  "<<left <<setw(2)<<setfill(' ')<<("Q")<<"               ";
        else if(c.table[i].second==13) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("K")<<"               ";
        else{
            cout<<"  "<<left<<setw(2)<<setfill(' ')<<c.table[i].second<<"               ";
        }
        Colorset(0X0F); cout<<" ";
    }
    cout<<endl;
    for(int i=0;i<11;i++){
        for(int j=0;j<sizee;j++){
            if(c.table[j].first==0){
                Colorset(0xF0); cout<<spade[i]; Colorset(0x0F); cout<<" ";
            }
            else if(c.table[j].first==1){
                Colorset(0xFC); cout<<heart[i]; Colorset(0x0F); cout<<" ";
            }
            else if(c.table[j].first==2){
                Colorset(0xF0); cout<<club[i];  Colorset(0x0F); cout<<" ";
            }
            else if(c.table[j].first==3){
                Colorset(0xFC); cout<<diamond[i];Colorset(0x0F);cout<<" ";
            }
        }
        cout<<endl;
    }
    for(int i=0;i<sizee;i++){
        if(c.table[i].first==0||c.table[i].first==2)
            Colorset(0xF0);
        else
            Colorset(0xFC);
        if(c.table[i].second==1) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("A")<<"               ";
        else if(c.table[i].second==11) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("J")<<"               ";
        else if(c.table[i].second==12) cout<<"  "<<left <<setw(2)<<setfill(' ')<<("Q")<<"               ";
        else if(c.table[i].second==13) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("K")<<"               ";
        else{
            cout<<"  "<<left<<setw(2)<<setfill(' ')<<c.table[i].second<<"               ";
        }
        Colorset(0X0F); cout<<" ";
    }
    cout<<endl;
    for(int i=0;i<sizee;i++){
        Colorset(0xF0); cout<<"                   "; Colorset(0x0F); cout<<" ";
    }
    cout<<endl;

    cout<<endl;
    output<<"你的手牌:"<<endl;
    sizee=c.player[pc].size();
        for(int i=0;i<sizee;i++){
        Colorset(0xF0); cout<<"                   "; Colorset(0x0F); cout<<" ";
    }
    cout<<endl;
    for(int i=0;i<sizee;i++){
        if(c.player[pc][i].first==0||c.player[pc][i].first==2)
            Colorset(0xF0);
        else
            Colorset(0xFC);
        if(c.player[pc][i].second==1) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("A")<<"               ";
        else if(c.player[pc][i].second==11) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("J")<<"               ";
        else if(c.player[pc][i].second==12) cout<<"  "<<left <<setw(2)<<setfill(' ')<<("Q")<<"               ";
        else if(c.player[pc][i].second==13) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("K")<<"               ";
        else{
            cout<<"  "<<left<<setw(2)<<setfill(' ')<<c.player[pc][i].second<<"               ";
        }
        Colorset(0X0F); cout<<" ";
    }
    cout<<endl;
    for(int i=0;i<11;i++){
        for(int j=0;j<sizee;j++){
            if(c.player[pc][j].first==0){
                Colorset(0xF0); cout<<spade[i]; Colorset(0x0F); cout<<" ";
            }
            else if(c.player[pc][j].first==1){
                Colorset(0xFC); cout<<heart[i]; Colorset(0x0F); cout<<" ";
            }
            else if(c.player[pc][j].first==2){
                Colorset(0xF0); cout<<club[i];  Colorset(0x0F); cout<<" ";
            }
            else if(c.player[pc][j].first==3){
                Colorset(0xFC); cout<<diamond[i];Colorset(0x0F);cout<<" ";
            }
        }
        cout<<endl;
    }
    for(int i=0;i<sizee;i++){
        if(c.player[pc][i].first==0||c.player[pc][i].first==2)
            Colorset(0xF0);
        else
            Colorset(0xFC);
        if(c.player[pc][i].second==1) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("A")<<"               ";
        else if(c.player[pc][i].second==11) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("J")<<"               ";
        else if(c.player[pc][i].second==12) cout<<"  "<<left <<setw(2)<<setfill(' ')<<("Q")<<"               ";
        else if(c.player[pc][i].second==13) cout<<"  "<<left<<setw(2)<<setfill(' ')<<("K")<<"               ";
        else{
            cout<<"  "<<left<<setw(2)<<setfill(' ')<<c.player[pc][i].second<<"               ";
        }
        Colorset(0X0F); cout<<" ";
    }
    cout<<endl;
    for(int i=0;i<sizee;i++){
        Colorset(0xF0); cout<<"                   "; Colorset(0x0F); cout<<" ";
    }
    cout<<endl;
    cout<<endl;

    return output;
}

int main(){
    COORD Sz;
    Sz.X=500; Sz.Y=1000;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),Sz);
    cout<<"撿紅點 ChineseRummy!!!"<<endl;
    system("pause");
    Colorset(0x06);
    cout<<"注意事項："<<endl;
    cout<<"有設定視窗大小，所以請勿將視窗最大化。"<<endl;
    cout<<"在非最大化的情況下，可以拉動橫向與直向卷軸來查看所有畫面"<<endl;
    Colorset(0x0C);
    cout<<"★若是按到最大化，請重新開啟程式★"<<endl;
    Colorset(0x0F);
    system("pause");
    Card cccrrr;
    while(cccrrr.gameover()){
        cccrrr.games();
    }
    return 0;
}

