#include <iostream>
#include<fstream>

using namespace std;

class PlayerNode{
public:
    int score, level;
    PlayerNode *next;

    PlayerNode(int s, int l){
        score=s;
        level=l;
        next =nullptr;
    }
};

class PlayerList{
private:
    PlayerNode *head;
public:
    PlayerList(){
        head = nullptr;
    }

    ~PlayerList(){
        clearList();
    }

    void clearList(){
        PlayerNode *current=head;
        while(current!=nullptr){
            PlayerNode *nextNode=current->next;
            delete current;
            current=nextNode;
        }
        head = nullptr;
    }

   void insertPlayer(int score, int level){
        PlayerNode *newNode=new PlayerNode(score,level);
        if(head==nullptr){
            head=newNode;
        }
        else{
            PlayerNode *temp=head;
            while(temp->next!=nullptr)
                temp=temp->next;
            temp->next=newNode;
        }
   }

   void saveToFile(const string& filename){
        ofstream out(filename);
        if(!out.is_open()){
            cout<<"Error opening file!"<<endl;
            return;
        }
        PlayerNode *temp=head;
        while(temp!=nullptr){
            out<<temp->score<<","<<temp->level<<endl;
            temp=temp->next;
        }
        out.close();
        cout<<"\nPlayer Data saved to file.\n";
   }

   void evaluatePerformance(){
       PlayerNode *temp=head;
       int i=1;
       while(temp!=nullptr){
            cout<<"\nPlayer: "<<i<<"\nScore="<<temp->score<<",Level="<<temp->level;
            i++;
            float bonus=0;
            string performance;

            if(temp->score>50){
                performance="Excellent";
                bonus=temp->score*0.3;
            }else if(temp->score>25){
                performance="Good";
                bonus=temp->score*0.2;
            }else if(temp->score>10){
                performance="Average";
                bonus=temp->score*0.1;
            }else{
                performance="Poor";
                bonus=0;
            }

            cout<<"\nPerformance: "<<performance;
            cout<<"\nBonusPoints: "<<bonus<<endl;
            temp=temp->next;
       }
   }
};

int main()
{
    PlayerList game;
    int choice;

    do{
        cout<<"\nWelcome to game score manager\n";
        cout<<"\nMenu\n";
        cout<<"1. Enter new player data\n";
        cout<<"2. View and evaluate existing player data\n";
        cout<<"3. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:{
                char confirm;
                cout<<"\nWarning: Entering new data will override the existing data.\n";
                cout<<"\nDo you still want to continue? (Y/N)\n";
                cin>>confirm;
                if(confirm=='Y' || confirm=='y'){
                    game.clearList();

                    int num;

                    cout<<"\nEnter the number of players: ";
                    cin>>num;

                    for(int i=0;i<num;i++){
                        int score,level;
                        cout<<"\nFor player "<<i+1;
                        cout<<"\nEnter score: ";
                        cin>>score;
                        cout<<"\nEnter level: ";
                        cin>>level;
                        game.insertPlayer(score,level);
                    }

                    game.saveToFile("scores.txt");
                    game.evaluatePerformance();
                }else{
                    cout<<"\nOperation cancelled.\n";
                    cout<<"Returning to main menu. \n";
                }
                break;
            }

            case 2:{
                game.clearList();

                ifstream in("scores.txt");
                if(!in.is_open()){
                    cout<<"No existing data found\n";
                    break;
                }

                int score, level;
                while(in>>score){
                    if(in.peek()==',')
                        in.ignore();
                    in>>level;
                    game.insertPlayer(score,level);
                }
                in.close();
                game.evaluatePerformance();
                break;
            }

            case 3:{
                cout<<"Exiting\n";
                break;
            }

            defalut:
                cout<<"invalid choice\n";
        }

    }while(choice!=3);
    return 0;
}
