#include <iostream>
#include <ctime>
using namespace std;

class Player
{
  protected:             // Defining data members as protected so that we can use them in child classes
  int maxHealth;         // Health at the start of game
  int baseDamage;        // Damage dealing capacity of the player
  int heal;              // healing capacity of the player
  int additionalDamage;  // will be decided at runtime
  int currentHealth;     // variable to store current health of player
  string player_name;    // player's name
  public:
  // Custom constructor
  Player(int _health, int _damage, int _heal,string _name) {
    // Initializing the data members through custom constructor
    maxHealth = _health;
    baseDamage = _damage;
    heal = _heal;
    currentHealth = maxHealth;
    player_name = _name;
  } 

  int GetHealth() {
    // function to get current health of player
    return currentHealth;
  }

  int DoBaseDamage() {
    cout << player_name << " is now Attacking. Dealing damage of: "<<baseDamage<<" HP\n";
    return baseDamage;
  };

  void DisplayStats() {
    cout << "Here are the current stats of "<<player_name<<endl;
    cout<<"Current Health: "<<currentHealth<<endl;
    cout<<"Damaging Capacity: "<<baseDamage<<" HP\n";
    cout<<"Healing Capacity: "<<heal<<" HP\n";
  }

  void TakeDamage(int _damage) {
    currentHealth -= _damage;
    if(currentHealth > 0) {
      cout <<player_name << " is taking damage of "<<_damage<<" HP\n";
      cout << "Current health of "<<player_name<<": "<<currentHealth<<" HP\n";
    } else {
      cout << player_name << " is dead\n";
    }
  }

  void Heal() {
    if(currentHealth != maxHealth) { // Don't Heal if health of player is already full
      currentHealth += heal;
      if(currentHealth >= maxHealth) {
        currentHealth = maxHealth;
        cout << player_name << " is completely healed. Ready to Kick Asses once again!\n";
        cout << "Current health of "<<player_name<<": " << currentHealth<<" HP\n";
      } else {
        cout << player_name<< " is healed. Its current health: "<<currentHealth<< " HP\n";
      } 
    }
    else { // when we try to heal the player if he is already at full health
      cout << "You have wasted this round. "<<player_name<< "can't be healed again. Suck it up NOOOB\n";
    }
  }
  // Virtual functions
  virtual int TotalDamage() {
    // Encapsulating All damage functions inside another separate function so in the main() function we can call
    // all damage functions at once
    return DoBaseDamage() + DoAdditionalDamage();
  }
  
  virtual void TotalHeal() {
    // Encapsulating heal function. Here we dont want to define it but we will define 
    // it in the child classes
    Heal();
  };

  // Pure Virtual Functions  
  
  virtual int DoAdditionalDamage() = 0;

  // destructor
  virtual ~Player() { }
};

class BrutePlayer : public Player
{
  private:
  int min = 10; 
  int max = 20; // additional damage range
  float additionalDamageProb = 0.3; // probability of doing additional damage
  public:
  BrutePlayer(int _hp, int _dp, int _heal,string _name):Player(_hp,_dp,_heal,_name) {
    cout<<endl <<"Our Almighty "<<player_name << " is Spawned. He is a strong as hercules:\n";
    cout << "Here are the current stats of "<<player_name<<endl;
    cout<<"Current Health: "<<currentHealth<<endl;
    cout<<"Damaging Capacity: "<<baseDamage<<" HP\n";
    cout<<"Healing Capacity: "<<heal<<" HP\n";
    cout<<"Additional damage between "<<min<<" ~ "<<max<<" HP with "<<additionalDamageProb*100<<" % probability\n";
    cout << "Special Ability: "<<player_name<< " has double the health than his opponent..:)\n\n";
  }

  int DoAdditionalDamage() {
    float x = rand()%10 / 10.0;
    additionalDamage = rand()%(max-min+1) + min; // generating random no between min and max random damage value
    // cout << "random no generated: "<<x<<" \n";
    if(x <= additionalDamageProb) {
      cout << "Bruty is enraged. He is doing additional Damage: "<<additionalDamage<<" HP\n";
      return additionalDamage;
    } else {
      return 0;
    }
    return additionalDamage;
  }
  
  virtual ~BrutePlayer() { }
};

class AgilePlayer : public Player
{
  private:
  int min = 3; int max = 10; // range for additional damage performed
  float additionalDamageProb = 0.1; // probability of additional damage (10%)
  float healthBoostProb = 0.2; // chances of using health boost
  public:
  // Initialize the attributes of Brute Player in the constructor
  // Here we are not taking user input for these values, so default constructor will do just fine
  AgilePlayer(int _hp, int _dp, int _heal,string _name):Player(_hp,_dp,_heal,_name) {
    cout<<endl <<player_name << " is Spawned. He is a healing master:\n";
    cout << "Here are the current stats of "<<player_name<<endl;
    cout<<"Current Health: "<<currentHealth<<endl;
    cout<<"Damaging Capacity: "<<baseDamage<<" HP\n";
    cout<<"Healing Capacity: "<<heal<<" HP\n";
    cout<<"Additional damage between "<<min<<" ~ "<<max<<" HP with "<<additionalDamageProb*100<<" % probability\n";
    cout << "Special Ability: "<<player_name<< " can heal himself by 50% of his original health\n\n";
  }
  int DoBaseDamage() {
    cout << "Agile Player is now Attacking. Dealing damage of: "<<baseDamage<<" HP\n";
    return baseDamage;
  }

  int DoAdditionalDamage() {
    float x = rand()%10 / 10.0;
    additionalDamage = rand()%(max-min+1) + min; // generating random no between min and max random damage value
    // cout << "random no generated: "<<x<<" \n";
    if(x <= additionalDamageProb) { 
      cout << "Agile is enraged. He is doing additional Damage: "<<additionalDamage<<" HP\n";
      return additionalDamage;
    } else {
      return 0;
    }
    return additionalDamage;
  }

  void HealBoost() {
    // Overloading the Heal function for Agile
    float x = rand()%10 / 10.0;
    if((x <= healthBoostProb) && (currentHealth != maxHealth)) {
      int boost = maxHealth/2;
      cout << "Agile is using health boost Ability. He's moving towards invincibility\n";
      currentHealth += boost; 
      cout << "Agile got health boost of: "<<boost<<" HP\n";
      if(currentHealth >= maxHealth) {
        currentHealth = maxHealth;
        cout << "Agile is completely healed. Its current health: "<<currentHealth<< " HP\n";
      } else {
        cout << "Current health of Agile: " << currentHealth<<" HP\n";
      }
    }
  }

  void TotalHeal() {
    // This method is only for agile player
    Heal(); // Normal Healing
    HealBoost(); // Healing boost with 20% probability
  }

  virtual ~AgilePlayer() {  }
};

class TacticalPlayer : public Player
{
  private:
  int min = 5; int max = 15; // range for additional damage performed
  float additionalDamageProb = 0.2; // probability of additional damage (20%)
  float deadShotProb = 0.05; // probability of finishing opponent in one blow
  int deadShotDamage = 200;
  public:
  TacticalPlayer(int _hp, int _dp, int _heal,string _name):Player(_hp,_dp,_heal,_name) {
    cout<<endl <<player_name << " is Spawned. He is a Japanese Sensei:\n";
    cout << "Here are the current stats of "<<player_name<<endl;
    cout<<"Current Health: "<<currentHealth<<endl;
    cout<<"Damaging Capacity: "<<baseDamage<<" HP\n";
    cout<<"Additional damage between "<<min<<" ~ "<<max<<" HP with "<<additionalDamageProb*100<<" % probability\n";
    cout << "Special Ability: "<<player_name<< " can become One Punch Man and can finish his opponent in one blow.. BOOM!\n\n";
  }
  int DoBaseDamage() {
    cout << "Tactical Player is now Attacking. Dealing damage of: "<<baseDamage<<" HP\n";
    return baseDamage;
  }
  
  int DoAdditionalDamage() {
    float x = rand()%10 / 10.0;
    additionalDamage = rand()%(max-min+1) + min; // generating random no between min and max random damage value
    if(x <= additionalDamageProb) {
      cout << "Tactical is Furious. He had enough. He is doing additional Damage: "<<additionalDamage<<" HP\n";
      return additionalDamage;
    } else {
      return 0;
    }
    return additionalDamage;
  }
  int DeadShot() {
    // This is the one punch man ability of our Tactical Hero
    float x = rand()%10 / 10.0;
    if(x <= deadShotProb) {
      cout << "\nTactical has become Saitama the Sensei. Using One Punch Ability...\n";
      return deadShotDamage;
    } else {
      return 0;
    }
  }
  int TotalDamage() {
    return DoBaseDamage() + DoAdditionalDamage() + DeadShot();
  }
  virtual ~TacticalPlayer() { }
};

class GameManager
{
  public:
  // Default constructor will print the welcome message to the players and rules of the game
  GameManager() {
    cout << "Welcome to the 2 player Battle Adventure Game. Let the Carnage begin...\n\n";
  cout << "Rules of the game:\n\n";
  cout << "1. Each player will get his/her turn to play moves\n";
  cout << "2. Player can either attack or heal or see his stats\n";
  cout << "3. Each player has to choose one of the hero from 3 different types of heroes\n";
  cout << "4. Each hero has different abilities. You can see these when you choose to display stats of your player\n";
  cout << "5. Press D or d to deal damage or H or h to heal\n";
  cout << "6. Player whose health drops to 0, will be dead and loses the game... Must a noob.. LOL\n";
  cout << "7. Each hero can deal additional damage after base damage if he gets pissed off!!\n";
  cout << "8. Last but not the least, some of the heroes have really dope superpowers, check them below before selecting your hero\n\n\n";
  cout << "There are 3 types of heroes each player can choose:\n\n";
  cout << "1) Brute => High health, high damage, Low healing capacity\n";
  cout << "Our Bruty has 30% probability of dealing additional damage in range of 10~20 HP\n\n\n";
  cout << "2) Agile => Low health, Low damage, High healing capacity\n";
  cout << "Agiles have 10% probability of pissing off and dealing additional damage of 3~10 HP\n";
  cout << "Agiles are smarty pants on their best day. They can give themselves huge health boost which will heal them by 50% of their health. There is 20% chance that Agiles will be on their best day\n\n\n";
  cout << "3) Tactical => Avg health, Avg damage and Avg healing capacity\n";
  cout << "This one has 20% chance of doing additional damage between 5~15 HP\n";
  cout << "But Dont consider this one as Average Joe. If this one is on his best day, he can become One Punch Man (Saitama Sensei) who can finish other player in one blow. Chance of tactical player to become one punch man is 5%\n\n\n";
  }
  
  // Code to validate user input for hero selection
  void InputChecker(int user_input) {
  // code block to check if user input is correct
  while((user_input >3) || (user_input <=0)) {
    cout << "Please Enter values between 1-3\n";
    cin>>user_input;
  } 
}
  // Function to Spawn the Player as per user input
  Player* PlayerSpawner(Player* pplayer, string player_name) {
    int x; // this is the variable for user input
    cout << player_name<<", Please select your hero. (1-> Brute, 2-> Agile, 3-> Tactical)\n";
    cin >> x;
    x = int(x);
    InputChecker(x);
    switch(x) {
    case 1: {
      return new BrutePlayer(200,25,8,"Bruty");
    }
    case 2: {
      return new AgilePlayer(80,10,20,"Agile");
    }
    case 3: {
      return new TacticalPlayer(100,15,15,"Tactical");
    }
    default: {
      return nullptr;
    }      
  }
  }
};

// Using enums for identifying which player is active
enum ActivePlayer {p1, p2} activePlayer;

class GameLoop
{
  public:
  GameLoop() {  }
  // p1 turn -> attack/heal, check if p2 is alive if yes then p2 turn else p1 wins the game
  // p2 turn -> attack/heal, check if p1 is alive if yes then p1 turn else p2 wins the game

  // Function to check whether the player is alive
  bool isAlive(Player* pplayer) {
  // Method to check if the player is Alive
  if(pplayer->GetHealth() > 0) {
    return true;
  } else {
    return false;
  }
  }
  // Function to validate player action
  void ActionInputChecker(char user_input) {
  while((user_input != 'd') && (user_input != 'h') && (user_input != 's')) {
    cout << "Please enter a valid input: ";
    cin>>user_input;
  }
  }

  // Function to Play
  void PlayerTurn(Player* activeP, Player* inactiveP) {
    char player_inp;
    activePlayer = p1; // at first active player would be player1
    while(true) {
      string player_name;
      if(activePlayer == p1) {
        player_name = "Player 1";
      } else {
        player_name = "Player 2";
      }
      cout << "\n"<<player_name<<"'s turn. Press d to damage or h to heal or s to see player stats: "<<endl;
      cin>>player_inp;
      ActionInputChecker(player_inp);
      if(player_inp == 'd') {
        inactiveP->TakeDamage(activeP->TotalDamage());
        if(!isAlive(inactiveP)) {
          cout << "\n\n"<<player_name<<" has WON! Congratulations :)\n\n";
          break;
        }
        if(activePlayer == p1) {
          activePlayer = p2; // if p1 is active, make p2 active and vice versa
        } else {
          activePlayer = p1;
        }
        swap(activeP, inactiveP); // swapping the pointers, active becomes inactive and vice versa
      } else if (player_inp == 'h') {
        activeP->TotalHeal();
        if(activePlayer == p1) {
          activePlayer = p2;
        } else {
          activePlayer = p1;
        }
        swap(activeP, inactiveP);
      }
      while (player_inp == 's') {
        activeP->DisplayStats();
        cout << "\n"<<player_name<<"'s turn. Press d to damage or h to heal or s to see player stats: "<<endl;
        cin >> player_inp;
      }
    }
    delete activeP;
    delete inactiveP; // to avoid memory leak
  } 
};


int main() 
{
  GameManager gameManager;
  GameLoop Loop;
  srand(time(0)); // setting seed for random no generator
  
  // Initializing Player pointers and assigning them to NULL
  Player *player1 = NULL;
  Player *player2 = NULL; 

  // Assigning Player objects as per user input
  player1 = gameManager.PlayerSpawner(player1, "Player 1");
  player2 = gameManager.PlayerSpawner(player2, "Player 2");

  // Game Loop Logic
  Loop.PlayerTurn(player1, player2);
}