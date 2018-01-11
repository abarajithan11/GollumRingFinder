int leftLine = 0;
int rightLine = 0;
bool isLineFound = false;
char lineFrom = ' ';

void detectLine()
{
  readIR();

  if(!isLineFound)
  {
    if(!irPanelVals[0] && !irPanelVals[1] && !irPanelVals[2] && !irPanelVals[3] && !irPanelVals[4] && !irPanelVals[6] && !irPanelVals[7])
    {
     lineFrom = ' ';
     isLineFound = false;
     return;
    }
  }


  if (!irPanelVals[0] && !irPanelVals[7] && !isLineFound) // No line in both ends and no line has been found
  {
    leftLine = 0;
    rightLine = 0;
    isLineFound = false;
    lineFrom = ' ';
    return;
  }

  if(irPanelVals[0] && irPanelVals[1] && irPanelVals[2] && irPanelVals[3] && irPanelVals[4] && irPanelVals[6] && irPanelVals[7])
  {
    taskStatus = 3;
    return;
  }

  if(!isLineFound && lineFrom == ' ')
  {
    if(irPanelVals[0]) lineFrom = 'l';
    else if (irPanelVals[7]) lineFrom = 'r';
  }

  for (char s = 1; s < 8; s++)
  {
    if (irPanelVals[s])
    {
      leftLine = s;
      isLineFound = true;
      break;
    }
  }

  if (isLineFound && leftLine == 7 && lineFrom == 'l')
  {
     taskStatus = 2;
     return;
  }

  for (char s = 7; s >= 1; s--)
  {
    if (irPanelVals[s])
    {
      rightLine = s;
      isLineFound = true;
      break;
    }
  }

  if (isLineFound && rightLine == 1&& lineFrom == 'r')
  {
     taskStatus = 2;
     return;
  }
  
}


void lineFound()
{
   motorRevBreak();
   analogWrite(13, 150);
   delay(2000);
   analogWrite(13, 0);
   Serial.println("LINE FOUND");

   delay(1000);
   
   taskStatus = 3;

   lineFrom = ' ';
   isLineFound = false;
   return;
}


void printIR()
{
  for(char s = 0; s < 8; s++)
  {
    Serial.print(irPanelVals[s]);
    Serial.print("  ");
  }
  Serial.println("");
}


