#include<Windows.h>
#include<stdio.h>
#include "res.h"
#include <cstdlib>
using namespace std;

bool isGameOnn = true;
bool isFirstPlayer = true;
int pola[3][3];
bool krzyzykWygral = false;
int licznik = 0;
int wspx=0;
int wspy=0;
void wyczysc(HWND hwndDlg);
void narysuj(HWND hwndDlg);
bool isFieldOccupiedByFirstPlayer[3][3];
bool isFieldOccupiedBySecondPlayer[3][3];
bool compisFirstPlayer;
void ruchKomputer(HWND hwndDlg);
bool wygrana();
bool wolnepole();
bool poziomLatwy;
bool ObliczWspolrzedneRuchuKomp();
bool znalazlem=false;

bool ObliczWspolrzedneRuchuKomp()
{

    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        if (isFieldOccupiedByFirstPlayer[i][j] == false && isFieldOccupiedBySecondPlayer[i][j] == false)
        {
          if (compisFirstPlayer == true)
            pola[i][j] = 1;
          else
            pola[i][j] = -1;
          if (wygrana() == true)
          {
            wspx = i;
            wspy = j;
            pola[i][j] = 0;
            isGameOnn = true;
            krzyzykWygral = false;
            return true;
          }
          pola[i][j] = 0;
        }

      }
    }

    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        if (isFieldOccupiedByFirstPlayer[i][j] == false && isFieldOccupiedBySecondPlayer[i][j] == false)
        { 
          if (compisFirstPlayer == true)
            pola[i][j] = -1;
          else
            pola[i][j] = 1;
          if (wygrana() == true)
          {
            wspx = i;
            wspy = j;
            pola[i][j] = 0;
            isGameOnn = true;
            krzyzykWygral = false;
            return true;
          }
          pola[i][j] = 0;
        }

      }
    }

  return false;
}

bool wolnepole()
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (pola[i][j] == 0)
        return true;
    }
  }
  return false;
}




void ruchKomputer(HWND hwndDlg)
{
  HDC hdc = GetDC(hwndDlg);
  bool wspolrzedne;
  bool znalazlem = false;

  if (poziomLatwy == true)
  {
    if (wolnepole() == true && wygrana() == false) 
    {
      while (!znalazlem)
      {
        wspx = rand() % 3;
        wspy = rand() % 3;
        if (isFieldOccupiedByFirstPlayer[wspx][wspy] == false && isFieldOccupiedBySecondPlayer[wspx][wspy] == false)
        {
          znalazlem = true;
        }


      }
    }
  }
  else
  {
    wspolrzedne=ObliczWspolrzedneRuchuKomp();
    if (wspolrzedne == false)
    {
      if (wolnepole() == true && wygrana() == false)
      {
        while (!znalazlem)
        {
          wspx = rand() % 3;
          wspy = rand() % 3;
          if (isFieldOccupiedByFirstPlayer[wspx][wspy] == false && isFieldOccupiedBySecondPlayer[wspx][wspy] == false)
          {
            znalazlem = true;
          }


        }
      }
    }
  }

  int nowyx = wspx * 100 + 90;
  int nowyy = wspy * 100 + 90;

  if (isFieldOccupiedByFirstPlayer[wspx][wspy] == false && isFieldOccupiedBySecondPlayer[wspx][wspy] == false)
  {
    if (compisFirstPlayer == true)
    {
      MoveToEx(hdc, nowyx - 30, nowyy - 30, NULL);
      LineTo(hdc, nowyx + 30, nowyy + 30);
      MoveToEx(hdc, nowyx - 30, nowyy + 30, NULL);
      LineTo(hdc, nowyx + 30, nowyy - 30);
      isFieldOccupiedByFirstPlayer[wspx][wspy] = true;
      pola[wspx][wspy] = 1;
      licznik++;
    }
    else
    {
      HBRUSH PedzelZiel, Pudelko;
      PedzelZiel = CreateSolidBrush(0x00FF00);
      Pudelko = (HBRUSH)SelectObject(hdc, PedzelZiel);
      Ellipse(hdc, nowyx - 30, nowyy - 30, nowyx + 30, nowyy + 30);
      SelectObject(hdc, Pudelko);
      DeleteObject(PedzelZiel);
      ReleaseDC(hwndDlg, hdc);
      isFieldOccupiedBySecondPlayer[wspx][wspy] = true;
      pola[wspx][wspy] = -1;
      licznik++;
    }
  }

  ReleaseDC(hwndDlg, hdc);
}

 void wyczysc(HWND hwndDlg)
 {
   HDC hdcOkno = GetDC(hwndDlg);
   HBRUSH PedzelBia, Pudelko;

   PedzelBia = CreateSolidBrush(0xFFFFFF);

   Pudelko = (HBRUSH)SelectObject(hdcOkno, PedzelBia);

   Rectangle(hdcOkno, 40, 40, 340, 340);
   SelectObject(hdcOkno, Pudelko);

   DeleteObject(PedzelBia);
   ReleaseDC(hwndDlg, hdcOkno);
 }
 
 void narysuj(HWND hwndDlg)
 {
   CHAR szText[500];
   HDC hdc = GetDC(hwndDlg);
   HPEN hMyPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
   SelectObject(hdc, hMyPen);
   MoveToEx(hdc, 40, 140, NULL);
   LineTo(hdc, 340, 140);
   MoveToEx(hdc, 40, 240, NULL);
   LineTo(hdc, 340, 240);
   MoveToEx(hdc, 140, 40, NULL);
   LineTo(hdc, 140, 340);
   MoveToEx(hdc, 240, 40, NULL);
   LineTo(hdc, 240, 340);
   DeleteObject(hMyPen);
   wsprintf(szText, "Aby wykonaæ ruch klikaj na planszy");
   TextOut(hdc, 0, 0, szText, strlen(szText));
   ReleaseDC(hwndDlg, hdc);
 }


bool wygrana()
{
  int zmienna = -10;
  for (int i = 0; i < 3; i++)
  {
    if ((pola[i][0]==pola[i][1]) && (pola[i][0]==pola[i][2]) && (pola[i][0] != 0))
    {
      isGameOnn = false;
      if (pola[i][0] == 1)
      {
        krzyzykWygral = true;
      }
      return true;
    }
  }
  for (int i = 0; i < 3; i++)
  {
    if ((pola[0][i] == pola[1][i]) && (pola[0][i] == pola[2][i]) && (pola[0][i] != 0))
    {
      isGameOnn = false;
      if (pola[0][i] == 1)
      {
        krzyzykWygral = true;
      }
      return true;
    }
  }
  if ((pola[0][0] == pola[1][1]) && (pola[0][0] == pola[2][2]) && (pola[1][1] != 0))
  {
    isGameOnn = false;
    if (pola[0][0] == 1)
    {
      krzyzykWygral = true;
    }
    return true;
  }
  if ((pola[2][0] == pola[1][1]) && (pola[2][0] == pola[0][2]) && (pola[1][1] != 0))
  {
    isGameOnn = false;
    if (pola[1][1] == 1)
    {

      krzyzykWygral = true;
    }
    return true;
  }
  return false;
}






INT_PTR CALLBACK DialogProc(HWND hwndDig, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:

    switch (HIWORD(wParam))
    {
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {


      case IDC_BUTTON10:
        krzyzykWygral = false;
        isFirstPlayer = true;
        isGameOnn = true;
        licznik = 0;

        HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
        CHAR szText[500];
        wsprintf(szText, "");
        SetWindowText(hwndStatic, szText);


        for (int i = 0; i < 3; i++)
        {
          for (int j = 0; j < 3; j++)
          {
            isFieldOccupiedByFirstPlayer[i][j] = false;
            isFieldOccupiedBySecondPlayer[i][j] = false;
            pola[i][j] = 0;
          }

        }

        wyczysc(hwndDig);
        narysuj(hwndDig);
        int zmienna = MessageBox(hwndDig, "Czy chcesz grac na trudnym poziomie ?", "Kó³ko i Krzy¿yk", MB_YESNO | MB_ICONQUESTION);
        if (zmienna == IDYES)
          poziomLatwy = false;
        else
          poziomLatwy = true;

        zmienna = MessageBox(hwndDig, "Czy chcesz rozpoczynaæ grê ?", "Kó³ko i Krzy¿yk", MB_YESNO | MB_ICONQUESTION);
        if (zmienna == IDYES)
          compisFirstPlayer = false;
        if (zmienna == IDNO)
        {
          compisFirstPlayer = true;
          ruchKomputer(hwndDig);
        }
        return TRUE;
      }

      return FALSE;

    }


    return FALSE;
  case WM_LBUTTONDOWN:
    if (isGameOnn == true && licznik < 9)
    {
      HDC hdc = GetDC(hwndDig);
      int x = LOWORD(lParam);
      int y = HIWORD(lParam);
      if ((x > 40 && x < 340) && (y > 40 && y < 340))
      {
        int FieldX = ((x - 40) / 100);
        int FieldY = ((y - 40) / 100);

        if (isFieldOccupiedByFirstPlayer[FieldX][FieldY] == false && isFieldOccupiedBySecondPlayer[FieldX][FieldY] == false)
        {

          x = ((x - 40) / 100) * 100 + 90;
          y = ((y - 40) / 100) * 100 + 90;
          if (compisFirstPlayer == true)
          {
            HBRUSH PedzelZiel, Pudelko;
            PedzelZiel = CreateSolidBrush(0x00FF00);
            Pudelko = (HBRUSH)SelectObject(hdc, PedzelZiel);
            Ellipse(hdc, x - 30, y - 30, x + 30, y + 30);
            SelectObject(hdc, Pudelko);
            DeleteObject(PedzelZiel);
            ReleaseDC(hwndDig, hdc);
            isFieldOccupiedBySecondPlayer[FieldX][FieldY] = true;
            pola[FieldX][FieldY] = -1;
            licznik++;


          }
          else
          {
            MoveToEx(hdc, x - 30, y - 30, NULL);
            LineTo(hdc, x + 30, y + 30);
            MoveToEx(hdc, x - 30, y + 30, NULL);
            LineTo(hdc, x + 30, y - 30);
            isFieldOccupiedByFirstPlayer[FieldX][FieldY] = true;
            pola[FieldX][FieldY] = 1;
            licznik++;

          }


          ReleaseDC(hwndDig, hdc);
          ruchKomputer(hwndDig);
          isFirstPlayer = !isFirstPlayer;

          if (wygrana() == true)
          {
            isGameOnn = false;
            if (krzyzykWygral == true)
            {
              HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
              CHAR szText[500];
              if (compisFirstPlayer == true)
              {

                wsprintf(szText, "Komputer cie pokona³ - restart");
                SetWindowText(hwndStatic, szText);
              }
              else
              {
                wsprintf(szText, "Brawo pokona³eœ komputer - restart");
                SetWindowText(hwndStatic, szText);
              }
            }
            else
            {
              HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
              CHAR szText[500];
              if (compisFirstPlayer == false)
              {

                wsprintf(szText, "Komputer cie pokona³ - restart");
                SetWindowText(hwndStatic, szText);
              }
              else
              {
                wsprintf(szText, "Brawo pokona³eœ komputer - restart");
                SetWindowText(hwndStatic, szText);
              }
            }
          }

        }
        if ((licznik == 9) && (wygrana() == false))
        {
          isGameOnn = false;
          HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
          CHAR szText[500];
          wsprintf(szText, "Brak roztrzygniêcia - restart");
          SetWindowText(hwndStatic, szText);
        }


      }
    }


  return TRUE;

  case WM_CLOSE:
    DestroyWindow(hwndDig);
    PostQuitMessage(0);
    return TRUE;
  }
  return FALSE;
}



int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, PSTR szCmdLIne, int iCmdShow)
{

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      isFieldOccupiedByFirstPlayer[i][j] = false;
      isFieldOccupiedBySecondPlayer[i][j] = false;
      pola[i][j] = 0;
    }
  }
  HWND hwndMainWindow = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  MSG msg = {};

  wyczysc(hwndMainWindow);
  narysuj(hwndMainWindow);
  int zmienna = MessageBox(hwndMainWindow, "Czy chcesz grac na trudnym poziomie ?", "Kó³ko i Krzy¿yk", MB_YESNO | MB_ICONQUESTION);
  if (zmienna == IDYES)
    poziomLatwy = false;
  else
    poziomLatwy = true;

  zmienna = MessageBox(hwndMainWindow, "Czy chcesz rozpoczynaæ grê ?", "Kó³ko i Krzy¿yk", MB_YESNO | MB_ICONQUESTION);
  if (zmienna == IDYES)
    compisFirstPlayer = false;
  if (zmienna == IDNO)
  {
    compisFirstPlayer = true;
    ruchKomputer(hwndMainWindow);
  }
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
