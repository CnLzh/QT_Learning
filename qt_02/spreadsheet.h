#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include<QTableWidget>

class Cell;
class SpreadsheetCompare;

class Spreadsheet : public QTableWidget
{
    Q_OBJECT
public:
    Spreadsheet(QWidget *parent = 0);
};

#endif // SPREADSHEET_H
