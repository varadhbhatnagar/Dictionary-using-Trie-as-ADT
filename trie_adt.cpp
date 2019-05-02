#include<bits/stdc++.h>
using namespace std;

class dictNode
{
    public:
        string data;

};

class trieNode
{
    public:
        map<char , trieNode *> mp;
        dictNode * dnode;
        bool is_word;

        trieNode()
        {
            dnode = NULL;
            is_word = false;
        }
   
};

dictNode * initialize_data(dictNode * dnode)
{
    string meaning;
    cout<<"\n Enter the meaning of this word\n";
    cin>>meaning;

    dnode->data = meaning;

    return dnode;
}


void insert_word(trieNode * root , string new_word)
{
    int i = 0;
    trieNode * iterRoot = root;

    while(i< new_word.size() && iterRoot->mp.find(new_word[i])!= iterRoot->mp.end())
    {
        iterRoot = iterRoot->mp[new_word[i]]; 
        i++;
    }

    if(i==new_word.size() && iterRoot->is_word==true)
    {
        cout<<"\n This word already exists in the dictionary : Cannot be inserted\n";
        return ;
    }

    while(i<new_word.size())
    {
        trieNode *t = new trieNode;
        iterRoot->mp[new_word[i]] = t; 
        i++;
        iterRoot = t;
    }

    if(i==new_word.size())
    {
        dictNode *d = new dictNode;
        d = initialize_data(d);

        iterRoot->is_word = true;
        iterRoot->dnode = d;
        cout<<"\n This word has been successfully inserted in the dictionary!\n";
    }

}

string find_update_word( trieNode * root , string query , bool find)
{
    int i = 0;
    trieNode * iterRoot = root;
    while(i< query.size() && iterRoot->mp.find(query[i])!=iterRoot->mp.end())
    {
        iterRoot = iterRoot->mp[query[i]]; 
        i++;
    }

    if(i==query.size() && iterRoot->is_word==true && find)
    {
        return iterRoot->dnode->data;
    }
    else if(i==query.size() && iterRoot->is_word==true && find==false)
    {
        string new_meaning;
        cout<<"\n Enter the new meaning of this word\n";
        cin>>new_meaning;

        iterRoot->dnode->data = new_meaning;
        return "\n The word meaning has been successfully updated\n";
        return iterRoot->dnode->data;
    }
    else
    {
        return "\n This word does not exist in the dictionary\n";
    }
    
}

bool delete_word(trieNode * root , string word , int i)
{
    if(i < word.size() && root->mp.find(word[i])!=root->mp.end())
    {
        bool status = delete_word(root->mp[word[i]], word , i+1);
        if(status == true)
            root->mp.erase(word[i]);

        if(i==0)
        {
            cout<<"\n Word deleted successfully\n";
            return true;
        }
    }

    if(i==word.size() && root->is_word)
    {
        root->is_word = false;
        delete root->dnode;

        if(root->mp.empty())
        {
            delete root;
            return true;
        }
       return false;
    }

}

void print_all(trieNode * root, string output)
{
    map<char , trieNode *> :: iterator it;

    if(root->is_word)
    {
        cout<<output<<" --> "<<root->dnode->data<<endl;
    }
    for(it = root->mp.begin(); it!=root->mp.end();it++)
    {
        print_all(it->second,output+(it->first));
    }
    
}

main()
{
    int option;
    char ch;
    trieNode *root = new trieNode;
    do
    {

    
        cout<<"********Dictionary using TRIE********";
        cout<<"\n MENU \n";
        cout<<"\n 1. Insert a word into the dictionary\n";
        cout<<"\n 2. Delete a word from the dictionary\n";
        cout<<"\n 3. Update the meaning of a word\n";
        cout<<"\n 4. Search for a word meaning\n";
        cout<<"\n 5. Print all words in dictionary\n";
        cout<<"\n Select and option from the Menu: \n";
        cin>>option;

        switch(option)
        {
            case 1: 
            {
                string new_word;

                cout<<"\n Enter the word that you want to insert\n";
                cin>>new_word;
                insert_word(root , new_word);

                break;
            }
            
            case 2:
            {
                string word;

                cout<<"\n Enter the word that you want to delete\n";
                cin>>word;
                if(find_update_word(root,word,1) == "\n This word does not exist in the dictionary\n")
                {
                    cout<<"\n This word does not exist in the dictionary\n";
                }
                else
                    delete_word(root , word , 0);

                break;
            }

            case 3:
            {
                string word, new_meaning;

                cout<<"\n Enter the word that you want to update\n";
                cin>>word;
                cout<<find_update_word(root ,word , false);

                break;
            }

            case 4:
            {
                string query , meaning;

                cout<<"\n Enter the word that you want to search\n";
                cin>>query;

                meaning = find_update_word(root , query , true);
                cout<<meaning;

                break;
            }

            case 5:
            {
                string output="";
                print_all(root,output);
            }
        }

        cout<<"\n Continue ? (Y/N)\n";
        cin>>ch;
    }while(ch=='Y');

}
