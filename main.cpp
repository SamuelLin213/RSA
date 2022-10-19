#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool checkPrime(int n);
void getNums(int& e, int& n, int len, vector<int>& msg);
bool primeFactors(int n, vector<int>& factors);
int inverseMod(int e, int phi);
int decipher(int c, int d, int n);
int convertText(int m);

int main()
{
  // prompt for number info
  vector<int> msg;
  //vector<char> msgCh;
  vector<int> primeFacs;
  int e, n, len;
  int phi;

  // get int inputs for e, n and len; store into vector msg
  getNums(e, n, len, msg);

  // Finding p and q
  if(!primeFactors(n, primeFacs))
  {
    cout << "Public key is not valid!" << endl;
    return 0;
  }

  // p and q found!
  int p = min(primeFacs[0], primeFacs[1]);
  int q = max(primeFacs[0], primeFacs[1]);
  phi = (p - 1) * (q - 1);

  if(__gcd(e, phi) != 1)
  {
    cout << "Public key is not valid!" << endl;
    return 0;
  }

  int d = inverseMod(e, phi);

  cout << p << " " << q << " " << phi << " " << d << endl;

  // Decipher the message
  int deciphered, ascii;
  for(int x = 0; x < int(msg.size()); x++)
  {
    deciphered = decipher(msg[x], d, n);
    cout << deciphered << " ";
  }
  cout << endl;
  for(int x = 0; x < int(msg.size()); x++)
  {
    deciphered = decipher(msg[x], d, n);
    ascii = convertText(deciphered);
    cout << char(ascii);
  }

  return 0;
}

bool checkPrime(int n)
{
  for(int x = 2; x*x <= n; x++)
  {
    if(n%x == 0)
    {
      return false;
    }
  }
  return true;
}

void getNums(int& e, int& n, int len, vector<int>& msg)
{
  cin >> e >> n >> len;

  for(int x = 0; x < len; x++)
  {
    int temp;
    cin >> temp;
    msg.push_back(temp);
  }
}

bool primeFactors(int n, vector<int>& factors)
{
    int prime;

    for(int x = 2; x < n; x++)
    {
      if(checkPrime(x))
      {
        if(n % x == 0 && (x != 1) && (n/x != 1) && (x != (n/x))) // check if both
        {
          factors = {x, (n/x)};
          return true;
        }
      }
    }

    return false;
}

int inverseMod(int e, int phi)
{
  int alpha = 1, beta = -1;
  int sum = (e * alpha) + (phi * beta);

  while(sum != 1)
  {
    if(sum > 1)
    {
      beta--;
    }
    else
    {
      alpha++;
    }
    sum = (e * alpha) + (phi * beta);
  }

  return alpha;
}

int decipher(int c, int d, int n)
{
  //return ((c % n) * c^(d-1)) % n;
  int a = 1, exp = d, b = c;
  int sum = 1;

  while(exp != 1)
  {
    if(exp % 2 != 0)
    {
      a *= b; // update constant at front
      exp -= 1; // decrement exponent to make it even
    }
    b *= b; // update base by squaring
    exp /= 2; // update exponent by dividing by 2

    // if either constant or base is larger than n, then perform modulo
    a = (a % n);
    b = (b % n);
  }

  sum = a * b;

  return sum % n;

}

int convertText(int m)
{
  if(m >= 5 && m <= 30)
  {
    m += 60;
  }
  else
  {
    switch(m)
    {
      case 31:
      {
        m = 32;
        break;
      }
      case 32:
      {
        m = 34;
        break;
      }
      case 33:
      {
        m = 44;
        break;
      }
      case 34:
      {
        m = 46;
        break;
      }
      case 35:
      {
        m = 39;
        break;
      }
    }
  }

  return m;
}
