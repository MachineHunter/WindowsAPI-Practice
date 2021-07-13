import win32com.client
from pathlib import Path

app = win32com.client.Dispatch("Excel.Application")

filepath = str(Path(r"./sample.xlsx").resolve())
workbook = app.Workbooks.Open(filepath, UpdateLinks=0, ReadOnly=True)
sheet    = workbook.Worksheets("Sheet1")

for row in range(2):
    for col in range(3):
        print(sheet.Cells.Item(row+1, col+1).Value)

app.Quit()
