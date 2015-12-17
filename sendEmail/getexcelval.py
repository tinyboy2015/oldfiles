# -*- coding: UTF-8 -*-
import  xdrlib ,sys
import xlrd
from email import encoders
from email.header import Header
from email.mime.text import MIMEText
from email.utils import parseaddr, formataddr
import smtplib

dics={
'sina.com':'smtp.sina.com.cn',
'vip.sina.com' :'smtp.vip.sina.com',
'sohu.com':'smtp.sohu.com',
'126.com' :'smtp.126.com',
'139.com' :'SMTP.139.com',
'163.com' :'smtp.163.com',
'qq.com'  :'smtp.qq.com',
'yahoo.com'   :'smtp.mail.yahoo.com',
'yahoo.com.cn':'smtp.mail.yahoo.com.cn',
'HotMail'   :'smtp.live.com',
'263.net'   :'smtp.263.net',
'263.net.cn':'smtp.263.net.cn',
'x263.net':'smtp.x263.net',
'21cn.com':'smtp.21cn.com',
'Foxmail' :'SMTP.foxmail.com',
'china.com':'smtp.china.com',
'tom.com'  :'smtp.tom.com',
'etang.com':'smtp.etang.com'
}


def open_excel(file= '工资范例.xlsx'):
    try:
        data = xlrd.open_workbook(file)
        return data
    except Exception as e:
        print(str(e))

def excel_table_byindex(file= '工资范例.xlsx',colnameindex=0,by_index=0):
    data = open_excel(file)
    table = data.sheets()[by_index]
    nrows = table.nrows #行数
    ncols = table.ncols #列数
    colnames =  table.row_values(colnameindex) #某一行数据 
    list =[]
    for rownum in range(1,nrows):
    	row=table.row_values(rownum)
    	if(row):
    		app={}
    		for i in range(len(colnames)):
    			app[colnames[i]]=row[i]
    		list.append(app)
    return list,colnames


def htmljoin(head,info):
	htmlinfo="""<base target="_blank" />
<style type="text/css">
::-webkit-scrollbar{ display: none; }
</style>
<style id="cloudAttachStyle" type="text/css">
#divNeteaseBigAttach, #divNeteaseBigAttach_bak{display:none;}
</style>
<style id="blockquoteStyle" type="text/css">blockquote{display:none;}</style>
<table border="1">
<tr>"""+r"%s"%head+"""</tr>"""+r"%s"%info+"""</tr>
</table>
<style type="text/css">
body{font-size:14px;font-family:arial,verdana,sans-serif;line-height:1.666;padding:0;margin:0;overflow:auto;white-space:normal;word-wrap:break-word;min-height:100px}
td, input, button, select, body{font-family:Helvetica, 'Microsoft Yahei', verdana}
pre {white-space:pre-wrap;white-space:-moz-pre-wrap;white-space:-pre-wrap;white-space:-o-pre-wrap;word-wrap:break-word;width:95%}
th,td{font-family:arial,verdana,sans-serif;line-height:1.666}
img{ border:0}
header,footer,section,aside,article,nav,hgroup,figure,figcaption{display:block}
</style>
<style id="ntes_link_color" type="text/css">a,td a{color:#138144}</style>"""
	return htmlinfo



def _format_addr(s):
    name, addr = parseaddr(s)
    return formataddr((Header(name, 'utf-8').encode(), addr))

def sendhtmlinfo(htmlinfomation,from_addr,password,to_addr,smtp_server):
	msg = MIMEText(htmlinfomation, 'html', 'utf-8')
	msg['From'] = _format_addr('gaos测试 <%s>' % from_addr)
	msg['To'] = _format_addr('管理员 <%s>' % to_addr)
	msg['Subject'] = Header('来自SMTP的问候……', 'utf-8').encode()
	server = smtplib.SMTP(smtp_server, 25)
	server.set_debuglevel(1)
	server.login(from_addr, password)
	server.sendmail(from_addr, [to_addr], msg.as_string())
	server.quit()


def main():
	from_addr = input('From: ')
	password = input('Password: ')
	#根据发件地址名确定需要的发送服务器
	smtp_server=dics[from_addr.split('@')[1]]
	print(smtp_server)
	tables,colNames = excel_table_byindex()
	htmlColname=[]#列名集
	personInfo=[]#个人信息集
	#生成头部标签
	for cname in colNames:
		if cname.find('邮箱')==-1:
			cname="<td>%s</td>"%cname
			htmlColname.append(cname);
	head='\n'.join(htmlColname)
	for row in tables:
		personInfo=[]
		for i in range(0,len(colNames)):
			judgeChildstr=str(row[colNames[i]]).find('@')
			#如果字段值不是邮箱，压入个人信息选项
			if judgeChildstr==-1:
				detail="<td>%s</td>"%row[colNames[i]]
				personInfo.append(detail)
			#如果为邮箱，则给to_addr赋值
			else: 
				to_addr=row[colNames[i]]
				print(to_addr)
		info='\n'.join(personInfo)
		htmlinfo=htmljoin(head,info)
		#print(htmlinfo)
		sendhtmlinfo(htmlinfo,from_addr,password,to_addr,smtp_server)

if __name__=="__main__":
    main()