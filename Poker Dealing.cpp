#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

string spade[11]={
"          *          ",
"         ***         ",
"        *****        ",
"       *******       ",
"     ***********     ",
"    *************    ",
"   ***************   ",
"  ******  *  ******  ",
"   ****  ***  ****   ",
"        *****        ",
"       *******       "};

string heart[11]={
"                     ",
"      ***   ***      ",
"     ***** *****     ",
"    *************    ",
"    *************    ",
"     ***********     ",
"       *******       ",
"        *****        ",
"         ***         ",
"          *          ",
"                     "};

string diamond[11]={
"          *          ",
"         ***         ",
"        *****        ",
"       *******       ",
"      *********      ",
"     ***********     ",
"      *********      ",
"       *******       ",
"        *****        ",
"         ***         ",
"          *          "};

string club[11]={
"                     ",
"         ***         ",
"        *****        ",
"       *******       ",
"    **  *****  **    ",
"   **** **********   ",
"  *****************  ",
"  *****   *   *****  ",
"   ***   ***   ***   ",
"        *****        ",
"       *******       "};



void Colorset(DWORD color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

class card{
    private:
        int deck[52];
        int l;
        int a;
    public:
        card();
        bool left_check(int);
        void print(int);
};

card::card(){
    srand(unsigned(time(0)));
    l=52;
    a=0;
    for(int i=0;i<52;i++)
        deck[i]=(i+1);
    random_shuffle(deck,deck+52);
}

bool card::left_check(int n){
    if(n<=l&&n>0){
        return 1;
    }
    else if(n>l){
        cout<<"牌推剩餘張數不夠，牌堆只剩"<<l<<"張"<<endl;
        return 0;
    }
    else{
        cout<<"請輸入正確的張數！"<<endl;
        return 0;
    }

}

void card::print(int n){
    for(int b=n;b>0;b--){
        Colorset(0xF0);cout<<"                     "; Colorset(0X0F);cout<<"   ";
    }
    cout<<endl;

    for(int j=0;j<n;j++){
        if(deck[a+j]<14){ //spade
            Colorset(0xF0);
            if(deck[a+j]==1) cout<<"  "<<left<<setw(2)<<("A")<<"                 ";
            else if(deck[a+j]==11) cout<<"  "<<left<<setw(2)<<("J")<<"                 ";
            else if(deck[a+j]==12) cout<<"  "<<left<<setw(2)<<("Q")<<"                 ";
            else if(deck[a+j]==13) cout<<"  "<<left<<setw(2)<<("K")<<"                 ";
            else
            cout<<"  "<<left<<setw(2)<<(deck[a+j])<<"                 ";
            Colorset(0X0F); cout<<"   ";
        }
        else if((deck[a+j])<27){ //heart
            Colorset(0xFC);
            if(deck[a+j]-13==1) cout<<"  "<<left<<setw(2)<<("A")<<"                 ";
            else if(deck[a+j]-13==11) cout<<"  "<<left<<setw(2)<<("J")<<"                 ";
            else if(deck[a+j]-13==12) cout<<"  "<<left<<setw(2)<<("Q")<<"                 ";
            else if(deck[a+j]-13==13) cout<<"  "<<left<<setw(2)<<("K")<<"                 ";
            else
            cout<<"  "<<left<<setw(2)<<(deck[a+j])-13<<"                 ";
            Colorset(0x0F); cout<<"   ";
        }
        else if((deck[a+j])<40){ //diamond
            Colorset(0xFC);
            if(deck[a+j]-26==1) cout<<"  "<<left<<setw(2)<<("A")<<"                 ";
            else if(deck[a+j]-26==11) cout<<"  "<<left<<setw(2)<<("J")<<"                 ";
            else if(deck[a+j]-26==12) cout<<"  "<<left<<setw(2)<<("Q")<<"                 ";
            else if(deck[a+j]-26==13) cout<<"  "<<left<<setw(2)<<("K")<<"                 ";
            else
            cout<<"  "<<left<<setw(2)<<(deck[a+j])-26<<"                 ";
            Colorset(0x0F); cout<<"   ";
        }
        else{ //club
            Colorset(0xF0);
            if(deck[a+j]-39==1) cout<<"  "<<left<<setw(2)<<("A")<<"                 ";
            else if(deck[a+j]-39==11) cout<<"  "<<left<<setw(2)<<("J")<<"                 ";
            else if(deck[a+j]-39==12) cout<<"  "<<left<<setw(2)<<("Q")<<"                 ";
            else if(deck[a+j]-39==13) cout<<"  "<<left<<setw(2)<<("K")<<"                 ";
            else
            cout<<"  "<<left<<setw(2)<<(deck[a+j])-39<<"                 ";
            Colorset(0x0F); cout<<"   ";
        }
    }
    cout<<endl;

    for(int i=0;i<11;i++){
        for(int j=0;j<n;j++){
            if(deck[a+j]<14){ //spade
                Colorset(0xF0);
                cout<<spade[i];
                Colorset(0x0F);
                cout<<"   ";
            }
            else if((deck[a+j])<27){ //heart
                Colorset(0xFC);
                cout<<heart[i];
                Colorset(0x0F);
                cout<<"   ";
            }
            else if((deck[a+j])<40){ //diamond
                Colorset(0xFC);
                cout<<diamond[i];
                Colorset(0x0F);
                cout<<"   ";
            }
            else{ //club
                Colorset(0xF0);
                cout<<club[i];
                Colorset(0x0F);
                cout<<"   ";
            }
        }
        cout<<endl;
    }

    for(int j=0;j<n;j++){
        if(deck[a+j]<14){ //spade
            Colorset(0xF0);
            if(deck[a+j]==1) cout<<"                 "<<right<<setw(2)<<("A")<<"  ";
            else if(deck[a+j]==11) cout<<"                 "<<right<<setw(2)<<("J")<<"  ";
            else if(deck[a+j]==12) cout<<"                 "<<right<<setw(2)<<("Q")<<"  ";
            else if(deck[a+j]==13) cout<<"                 "<<right<<setw(2)<<("K")<<"  ";
            else
            cout<<"                 "<<right<<setw(2)<<(deck[a+j])<<"  ";
            Colorset(0x0F); cout<<"   ";
        }
        else if((deck[a+j])<27){ //heart
            Colorset(0xFC);
            if(deck[a+j]-13==1) cout<<"                 "<<right<<setw(2)<<("A")<<"  ";
            else if(deck[a+j]-13==11) cout<<"                 "<<right<<setw(2)<<("J")<<"  ";
            else if(deck[a+j]-13==12) cout<<"                 "<<right<<setw(2)<<("Q")<<"  ";
            else if(deck[a+j]-13==13) cout<<"                 "<<right<<setw(2)<<("K")<<"  ";
            else
            cout<<"                 "<<right<<setw(2)<<(deck[a+j])-13<<"  ";
            Colorset(0x0F); cout<<"   ";
        }
        else if(deck[a+j]<40){ //diamond
            Colorset(0xFC);
            if(deck[a+j]-26==1) cout<<"                 "<<right<<setw(2)<<("A")<<"  ";
            else if(deck[a+j]-26==11) cout<<"                 "<<right<<setw(2)<<("J")<<"  ";
            else if(deck[a+j]-26==12) cout<<"                 "<<right<<setw(2)<<("Q")<<"  ";
            else if(deck[a+j]-26==13) cout<<"                 "<<right<<setw(2)<<("K")<<"  ";
            else
            cout<<"                 "<<right<<setw(2)<<(deck[a+j])-26<<"  ";
            Colorset(0x0F); cout<<"   ";
        }
        else{ //club
            Colorset(0xF0);
            if(deck[a+j]-39==1) cout<<"                 "<<right<<setw(2)<<("A")<<"  ";
            else if(deck[a+j]-39==11) cout<<"                 "<<right<<setw(2)<<("J")<<"  ";
            else if(deck[a+j]-39==12) cout<<"                 "<<right<<setw(2)<<("Q")<<"  ";
            else if(deck[a+j]-39==13) cout<<"                 "<<right<<setw(2)<<("K")<<"  ";
            else
            cout<<"                 "<<right<<setw(2)<<(deck[a+j])-39<<"  ";
            Colorset(0x0F); cout<<"   ";
        }
    }
    cout<<endl;

    for(int b=n;b>0;b--){
        Colorset(0xF7); cout<<"                     "; Colorset(0x0F); cout<<"   ";
    }
    cout<<endl;

    a+=n;
    l-=n;
    cout<<"牌堆剩餘"<<l<<"張"<<endl;
}

int main(){
    cout<<"請先將視窗最大化，以獲得單行更多的空間"<<endl;
    system("pause");
    Colorset(0x0C);cout<<"請按照視窗大小選擇適合的單行牌數，選擇牌數超過視窗大小將會溢出至下一行"<<endl;Colorset(0x0F);
    system("pause");
    Colorset(0x06);cout<<"發生此種情形，請將每行輸出牌數減少，以獲得正常卡牌顯示"<<endl;Colorset(0x0F);
    system("pause");
    cout<<endl;
    while(cout<<"新的一副牌已洗好"<<endl<<endl){
        card poke;
        while(cout<<"請輸入一排要發放的撲克牌張數，或是輸入0重新獲得一副新牌"<<endl){
            int n;
            cin>>n;
            if(n==0) break;
            if(poke.left_check(n)){
                poke.print(n);
            }
            cout<<endl;
        }
        cout<<endl;
    }
    return 0;
}
