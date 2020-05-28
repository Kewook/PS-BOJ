/*
오답1. 52번줄 op[o].robot을 op[0].robot으로 오타냄
(index변수로 o쓰지말자;;)
*/
#include<iostream>

using namespace std;

struct Operation {
   int robot;
   char oper;
   int loop;
};

struct Pair{
   int ypos, xpos, dir;
};

Operation op[105];
Pair robot[105];

//차례로 동, 북, 서, 남
int dy[] = { 0,1,0,-1 }, dx[] = { 1,0,-1,0 };
int ar[105][105];
int A, B, N, M;

bool isTrue(int idx) {
   int ypos = robot[idx].ypos, xpos = robot[idx].xpos;

   //벽
   if (ypos < 1 || xpos < 1 || ypos > B || xpos > A) {
      cout << "Robot " << idx << " crashes into the wall\n";
      return false;
   }

   //다른로봇
   for (int i = 1; i <= N; i++) {
      if (i == idx)continue;
      int typos = robot[i].ypos, txpos = robot[i].xpos;
      if (ypos == typos && xpos == txpos) {
         cout << "Robot " << idx << " crashes into robot " << i << "\n";
         return false;
      }
   }

   return true;
}

bool simulate() {
   for (int o = 0; o < M; o++) {
      //수행
      for (int i = 0; i < op[o].loop; i++) {
         int idx = op[o].robot;

         if (op[o].oper == 'F') {
            robot[idx].ypos += dy[robot[idx].dir];
            robot[idx].xpos += dx[robot[idx].dir];
         }
         else if (op[o].oper == 'R') {
            if (robot[idx].dir == 0)robot[idx].dir = 3;
            else robot[idx].dir--;
         }
         else if (op[o].oper == 'L') {
            robot[idx].dir = (robot[idx].dir + 1) % 4;
         }
         
         //체크
         if (!isTrue(idx)) return false;
      }
   }
   return true;
}

int main(void) {
   ios::sync_with_stdio(0);
   cin.tie(NULL); cout.tie(NULL);

   cin >> A >> B >> N >> M;
   
   for (int i = 1; i <= N; i++) {
      int x, y;
      char direction;
      cin >> x >> y >> direction;

      switch (direction) {
      case 'E': direction = 0;
         break;
      case 'N': direction = 1;
         break;
      case 'W': direction = 2;
         break;
      case 'S': direction = 3;
         break;
      }

      robot[i] = { y, x, direction };
   }
   
   for (int i = 0; i < M; i++) {
      int rb, l;
      char oper;
      cin >> rb >> oper >> l;
      op[i] = { rb, oper, l };
   }

   if (simulate())cout << "OK";

   return 0;
}