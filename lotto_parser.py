from bs4 import BeautifulSoup
import requests, string, sys

#num = sys.argv[1]
num = "814"

URL = "http://www.nlotto.co.kr/gameResult.do?method=byWin&drwNo=" + num

html = requests.get(URL)
html = html.content
soup = BeautifulSoup(html,'html.parser')

# ---------------------------------------------------------------------------------------------

number = []
temp = [] 

num_par = soup.find_all("meta", id = "desc")
temp = str(num_par).split(",")

for i in range(0,6):
    if i == 0:
        tmp = temp[i].replace('[<meta content="나눔로또 ','')
        tmp = tmp.replace(num,'')
        tmp = tmp.replace('회 당첨번호 ','')
        
        number.append(tmp)
    elif i == 5:
        tmp = temp[i].replace('명','')
        tmp = tmp.replace('. 1등 총 ','\n')
        tmp_0 = []
        tmp_0 = tmp.split("+")
        number.append(tmp_0[0])
        number.append(tmp_0[1])
    else:
        number.append(temp[i])

# ---------------------------------------------------------------------------------------------

total_par = soup.find_all("td","rt")

edit_1 = []
edit_2 = []

total_money = []
total_human = []
human_money = []

for i in range(0,20):
    tmp = str(total_par[i]).split("<")
    edit_1.append(tmp)

    tmp = str(edit_1[i]).split(">")
    edit_2.append(tmp)

    if (i % 4) == 0 :
        tmp = edit_2[i][2].replace("', '/strong","")
        total_money.append(tmp)
    elif (i % 4) == 1 :
        tmp = edit_2[i][1].replace("', '/td","명")
        total_human.append(tmp)
    elif (i % 4) == 2 :
        tmp = edit_2[i][1].replace("', '/td","")
        human_money.append(tmp)

#number - 당첨번호
#total_money - 총 당첨금액
#total_human - 총 당첨된 사람 수
#human_money - 1인당 받는 돈

def _for(a,b):
    for i in range(0,a):
        if (i == (a-1)):
            f.write(str(b[i]))
        else:
            f.write(str(b[i])+",")
    f.write("\n")


f = open('lotto_db.w','w')


f.write(str(num)+"\n")
_for(7,number)
_for(5,total_money)
_for(5,total_human)
_for(5,human_money)

f.close()

# pyinstaller -F lotto_parser.py

