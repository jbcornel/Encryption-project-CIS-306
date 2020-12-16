//Program Name: Doubly Encrypted Message Program

//Program Description: An algorithm capable of taking a public key and a message 
//(which will consist of two composite natural numbers) and calculate its GCD and LCM
//which will function as the encrypted message. 
//Then, using RSA Encryption, the private key will be obtained. 
//Next, the private key and encrypted message will be "sent" and decrypted. 
//Preforming this process in reverse to get the originally encrypted message and the sender’s public key.

//Date: 12/18/2020

//Programmers: Joseph Cornell, Christian Cuevas, James Elugbemi

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

//Determine if an input is composite, runs in O(n / 2) :
bool isComposite(int N)
{
    //Let N be the input quantity; iterate up to N / 2 times; let i describe the current state the of iterations
    for (int i = 2; i < N/2; i++)
    {
        //If N mod i has no remainder it is composite
        if (N % i == 0)
        {
            //Stop iterating
            return true;
        }
    }
    
    //If this statement is reached N is prime
    return false;
}
    
//Calculate the GCD of composite inputs p and q, runs in O(n) :
int calcGCD(int p, int q)
{
    //Let p be greater than or equal to q 
    if (p < q)
    {
        int swap = p;
        p = q;
        q = swap;
    }
    
    //Let r be the result of p mod q
    int r = p % q;

    //If r is 0 return q   
    if (r == 0)
    {
        return q;
    }

    //Otherwise find the GCD of q and r
    return calcGCD(q, r);
}
    
//Calculate the LCM of composite inputs pand q, runs in O(1) :
int calcLCM(int p, int q)
{
    //Let N be the product of p and q
    int N = p * q;

    //Divide N by the GCD of p and q
    //The result is the LCM
    return N / calcGCD(p, q);
}
 
//Calculate the modulo inverse of inputs eand n, runs in O(n) :
int calcModInverse(int e, int n)
{
    //Let n be greater than e
    if (n < e)
    {
        int swap = e;
        e = n;
        n = swap;
    }

    //Set e equal to itself mod n
    e = e % n;

    //Let d equal 1, iterate up to n many times incrementing d for each iteration
    for (int d = 1; d < n; d++)
    {
        //If the product of e and d mod n is equal to one we’ve found d the modular inverse of e
        if ((e * d) % n == 1)
        {
            return d;
        }
    }

}

//Perform RSA encryption of inputs x e and N, runs in O(3n):
int calcRSAEncrypt(int x, int e, int N)
{
    //Let b be the conversion of e into its binary equivalent
    vector <int> b;
    b.resize(32, 0);

    for (int i = 0; e > 0; i++)
    {
        b.at(i) = e % 2;
        e = e / 2;
    }

    int it = 31;
    while (it >=0)
    {
        if (b.at(it) != 0)
        {
            break;
        }

        it--;
    }

    b.resize(it + 1);

    //Let m be an integer sequence the length of b
    vector <int> m;
    m.resize(b.size(), 0);

    //Store x mod N in m’s first position
    m.at(0) = x % N;
    
    //Iterate b’s length - 1 many times,
    for (int i = 1; i < b.size(); i++)
    {
        //Store(the square of the previous iteration’s x mod N) mod N at the current iteration’s corresponding position in m
        m.at(i) = (m.at(i - 1) * m.at(i - 1)) % N;
    }

    //Iterate through b’s entirety
    for (int i = 0; i < b.size(); i++)
    {
        //If b’s corresponding position contains a 0 set the corresponding position in m to 1
        if (b.at(i) == 0)
        {
            m.at(i) = 1;
        }
    }

    //Iterate through m’s entirety
    for (int i = 1; i < m.size(); i ++)
    {
        //If this isn’t the last iteration 
        //Store the product of the current and next iteration mod N in the next iteration
        m.at(i) = (m.at(i - 1) * m.at(i)) % N;
            
    }
        
    //m’s last position is the encryption of x
    return m.back();
}

//Reverse operate the weak message, runs in O(1)
int getMessage(int GL, int b)
{
    float a = GL / b;

    return int(a);
}

int main()
{
    int publicKey = 0;
    int compositeA = 0;
    int compositeB = 0;

    //Obtain info from user
    cout << "Welcome to the Doubly Encrypted Message Program" << endl;
    cout << "Enter E to encrypt from a file or D to decrypt from a file" << endl;
    
    char response = 'R';
    bool validResponse = false;
    
    while (validResponse == false)
    {
        cin >> response;

        switch (response)
        {
        case 'E':
        case 'e':
        case 'D':
        case 'd':
            validResponse = true;
            break;
        default:
            cout << "Please enter a valid response" << endl;
            cout << "Enter E to encrypt from a file or D to decrypt from a file" << endl;
            break;
        }

    }

    string inputString;
    string outputString;
    ifstream infile;
    ofstream outfile;

    int GCD;
    int LCM;

    int weakMessage;
    int StrongMessage;

    int privateKey;

    switch (response)
    {
    case 'E':
    case 'e':
        cout << "Please enter the file you would like to read from" << endl
            << "It should contain the public key and the two composite natural numbers you would like to encrypt" << endl;
        
        cin >> inputString;

        infile.open(inputString);

        while (infile.fail())
        {
            cout << "The file could not be opened, please adjust the file directory and/or reenter the file name" << endl;
            cin >> inputString;

            infile.open(inputString);
        }

        infile >> publicKey;
        infile >> compositeA;
        infile >> compositeB;

        if ( ( !isComposite(compositeA) ) || ( !isComposite(compositeB) ) )
        {
            cout << "In order for the double encryption to work, please alter the file to have public key followed by two composite numbers" << endl;
            cout << "The program will now close";
            return 1;
        }

        //Calculate GCD and LCM
        GCD = calcGCD(compositeA, compositeB);
        LCM = calcLCM(compositeA, compositeB);

        weakMessage = GCD * LCM;

        //Encrpyt with RSA
        StrongMessage = calcRSAEncrypt(weakMessage, publicKey, 403);

        infile.close();

        //Send privateKeys and encrypted message
        privateKey = calcModInverse(publicKey, 360);

        cout << "Enter the name of the file you would like to write the encrypted information to" << endl;
        
        cin >> outputString;

        outfile.open(outputString);

        outfile << privateKey << " " << LCM << " " << GCD << " " << compositeB << " " << StrongMessage;

        outfile.close();

        break;
    case 'D':
    case 'd':
        //Reverse process
        cout << "Please enter the file you would like to read from" << endl;
        
        cin >> inputString;

        infile.open(inputString);

        while (infile.fail())
        {
            cout << "The file could not be opened, please adjust the file directory and/or reenter the file name" << endl;
            cin >> inputString;

            infile.open(inputString);
        }

        infile >> privateKey;
        infile >> LCM;
        infile >> GCD;
        infile >> compositeB;
        infile >> StrongMessage;

        publicKey = calcModInverse(privateKey, 360);

        weakMessage = LCM * GCD;

        compositeA = getMessage(weakMessage, compositeB);

        cout << "Enter the name of the file you would like to write the decrypted information to" << endl;

        cin >> outputString;

        outfile.open(outputString);

        outfile << publicKey << " " << compositeA << " " << compositeB;


        break;
    default:
        break;
    };

    
    cout << "Your information can be found in " << outputString << endl;

    outfile.close();

        
    return 0;
}

