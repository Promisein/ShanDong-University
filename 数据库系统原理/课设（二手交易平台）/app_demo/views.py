from django.http import HttpResponseRedirect
from django.shortcuts import render, redirect
from django.shortcuts import HttpResponse
from app_demo.models import user_password
from django.db.models import Max

from . import models

def login(request):
    # return redirect("main/")
    if request.method == "POST":
        id = request.POST.get('id').strip()
        password = request.POST.get('password').strip()
        res = models.user_password.objects.filter(id = id).first()
        if res:
            if res.password == password:
                print("登录成功！")
                request.session["user_id"] = id
                request.COOKIES["user_id"]= id
                return redirect("/main/")
    return render(request,"login.html")

from app_demo.models import user_password,user_information
def register(request):
    global res
    max_id = models.user_password.objects.aggregate(Max('id'))
    newid = max_id['id__max']
    newid = newid + 1
    if request.method=="POST":
        name = request.POST.get("name")
        password = request.POST.get("password")
        gender = request.POST.get("gender")
        Telephone = request.POST.get("Telephone")
        QQ_number = request.POST.get("QQ_number")
        model_password = models.user_password.objects
        model_information = models.user_information.objects
        try:
             res = model_password.create(password = password)
        except Exception:
            print("用户注册失败")
        if res:
            try:
                res = model_information.create(name=name, gender=gender, Telephone=Telephone, QQ_number=QQ_number)
                max_id = models.user_password.objects.aggregate(Max('id'))
                id = max_id['id__max']
                string_id = str(id)
                request.session["user_id"] = string_id
                request.COOKIES["user_id"] = string_id
            except Exception:
                print("用户注册失败")
            if res:
                return redirect("/main/")
    return render(request,"register.html",{'max':newid})

def buy(request):
    if 'user_id' in request.session:
        print("buy")
        o = request.session['user_id']
        s=d
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)

        b=models.goods_information.objects.filter(id = num).first()
        c = models.user_information.objects.all()
        g = models.user_information.objects.filter(id=o).first()

        global buyer_offer

        if request.method == "POST":
            buyer_offer = request.POST.get("buyer_offer")
            print(buyer_offer)

        if request.method == "POST":
            a1 = request.POST.get("sc")
            if a1 == "20":
                models.shopping_cart.objects.create(User_id=o,Goods_id=num,State="1")

        return render(request,"buy.html",{'good':b,'sellers':c,'buyer':g})
    else:
        return redirect('/main/login/')

def newmain(request):
    print("newmain")
    global d
    a0 = models.goods_information.objects.all()
    if request.method == "POST":
        a1=request.POST.get("good")
        print("成功提交")
        #print(type(a1))
        if len(a1)!=0:
            d=a1
            return redirect("buy/")
    return render(request, "cainiaomainpage.html", {'goods': a0})

def goods(request):
    if 'user_id' in request.session:
        return render(request, "goods.html")
    else:
        return redirect('/main/login/')

def personal_information(request):
    if 'user_id' in request.session:
        i=request.session['user_id']
        b=models.user_information.objects.filter(id = i).first()
        return render(request, "personal_information.html",{'bb':b})
    else:
        return redirect('/main/login/')

def main(request):
     res = models.goods_information.objects.all()
     res2 = models.user_information.objects.all()
     return render(request, "main.html", {'goods': res, 'seller': res2})

def change_my_information(request):
    if 'user_id' in request.session:
        return render(request,"change_my_information.html")
    else:
        return redirect('/main/login/')

def change_my_name(request):
    if 'user_id' in request.session:
    # s=requests.get('http://127.0.0.1:8000/login/main/change_my_information/')
        res = models.user_information.objects.all()
    # s=request.session["user_id"]
    # print(s)
        s = request.session['user_id']
    # 获取的字符串类型s
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)
    # 把字符串id即s转化为数字num

    # 修改个人姓名
        if request.method == "POST":
            name = request.POST.get("name")
            model_information = models.user_information.objects
            if name:
                res2 = model_information.filter(id = num).update(name = name)
                print("修改成功")
        return render(request, "change_my_name.html", {'name_': res, 'ss': num})
    else:
        return redirect('/main/login/')

def change_my_telephone(request):
    if 'user_id' in request.session:
    # s=requests.get('http://127.0.0.1:8000/login/main/change_my_information/')
        res = models.user_information.objects.all()
    # s=request.session["user_id"]
    # print(s)
        s = request.session['user_id']
    # 获取的字符串类型s
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)
    # 把字符串id即s转化为数字num

        if request.method == "POST":
            Telephone = request.POST.get("Telephone")
            model_information = models.user_information.objects
            if Telephone:
                res2 = model_information.filter(id = num).update(Telephone = Telephone)
                print("修改成功")
        return render(request, "change_my_telephone.html", {'name_': res, 'ss': num})
    else:
        return redirect('/main/login/')

def change_my_gender(request):
    if 'user_id' in request.session:
    # s=requests.get('http://127.0.0.1:8000/login/main/change_my_information/')
        res = models.user_information.objects.all()
    # s=request.session["user_id"]
    # print(s)
        s = request.session['user_id']
    # 获取的字符串类型s
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)
    # 把字符串id即s转化为数字num

        if request.method == "POST":
            gender = request.POST.get("gender")
            model_information = models.user_information.objects
            if gender:
                res2 = model_information.filter(id = num).update(gender = gender)
                print("修改成功")
        return render(request, "change_my_gender.html", {'name_': res, 'ss': num})
    else:
        return redirect('/main/login/')

def change_my_QQNumber(request):
    if 'user_id' in request.session:
    # s=requests.get('http://127.0.0.1:8000/login/main/change_my_information/')
        res = models.user_information.objects.all()
    # s=request.session["user_id"]
    # print(s)
        s = request.session['user_id']
    # 获取的字符串类型s
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)
    # 把字符串id即s转化为数字num

        if request.method == "POST":
            QQ_number = request.POST.get("QQ_number")
            model_information = models.user_information.objects
            if QQ_number:
                res2 = model_information.filter(id = num).update(QQ_number = QQ_number)
                print("修改成功")
        return render(request, "change_my_QQNumber.html", {'name_': res, 'ss': num})
    else:
        return redirect('/main/login/')

def UpLoadInfo(request):
    if request.method == 'POST':
        # img = request.FILES.get('photo')
        # user = request.FILES.get('photo').name
        new_img = models.Avatar(
            photo = request.FILES.get('photo'),  # 拿到图片
            user = request.FILES.get('photo').name  # 拿到图片的名字
        )
        new_img.save()  # 保存图片
        return render(request, 'user_list.html')
    return render(request, 'upload.html')

def put_goods(request):
    if 'user_id' in request.session:
        global res

        res = models.goods_information.objects.all()
        res1 = models.label.objects.all()

        res2 = models.user_information.objects.all()
    # s=request.session["user_id"]



    # print(s)
        s = request.session['user_id']
    # 获取的字符串类型s
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)
    # 把字符串id即s转化为数字num


        if request.method == "POST":
            Goods_name = request.POST.get("Goods_name")
            Peice = request.POST.get("Peice")
            Decription = request.POST.get("Decription")
            Label_name = request.POST.get("Label_id")
            model_goods = models.goods_information.objects
            UpLoadInfo(request)
        # for i in res:
        #     for j in res1:
        #         if i.Label_id == j.id:
        # print(Peice)
        # print(num)
            try:
                for i in res1:
                    if i.name == Label_name:
                        Label_id = i.id
            except:
                print("没有对应的标签")
            try:
                res3 = model_goods.create(Goods_name = Goods_name, User_id = num,Peice=Peice, Label_id = Label_id, Decription = Decription)
            except Exception:
                print("上架商品失败！")
        return render(request, "put_goods.html", {'label_name' : res1 })
    else:
        return redirect('/main/login/')

def transaction(request):
    if 'user_id' in request.session:
        res = models.user_information.objects.all()
        s = request.session['user_id']
        # 获取的字符串类型s
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)
        # 把字符串id即s转化为数字num

        # 当前的buyer_id 为 num
        buyerID = num

        # goods_id 为 全局变量 d
        goodsID = d

        # 获得当前goodsId的全部信息
        goodsInformation = models.goods_information.objects.filter(id=goodsID).first()

        false = 2
        success = 1
        mid = 0  # 未处理状态

        model_transaction = models.Transaction.objects
        model_goodsInformation = models.goods_information.objects
        try:
            print("交易信息表单")
            print(buyer_offer)
            models.Transaction.objects.create(Goods_id = goodsID, if_success = mid, Buyer_id = buyerID,
                                              Seller_id = goodsInformation.User_id,
                                              Buyer_offer = buyer_offer, Seller_offer = goodsInformation.Peice)

            models.shopping_cart.objects.create(User_id=buyerID, Goods_id=goodsID, State="2")
            # 更改商品状态
            res3 = model_goodsInformation.filter(id=goodsID).update(State=1)
        except Exception:
            print("交易出现信息错误！")

        return render(request, 'transaction.html')
    else:
        return redirect('/main/login/')


def Account_management(request):
    if 'user_id' in request.session:
        i = request.session['user_id']
        f = models.user_password.objects.filter(id=i).first()
        b = models.user_information.objects.filter(id=i).first()
        return render(request,"Account_management.html",{'ff':f,'bb':b})
    else:
        return redirect('/main/login/')

def change_password(request):
    if 'user_id' in request.session:
    # s=requests.get('http://127.0.0.1:8000/login/main/change_my_information/')
        res = models.user_password.objects.all()
    # s=request.session["user_id"]
    # print(s)
        s = request.session['user_id']
    # 获取的字符串类型s
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)
    # 把字符串id即s转化为数字num

    # 修改个人mima
        if request.method == "POST":
            password = request.POST.get("password")
            model_information = models.user_password.objects
            if password:
                res2 = model_information.filter(id=num).update(password=password)
                print("修改成功")
        return render(request, "change_password.html", {'password_': res, 'ss': num})
    else:
        return redirect('/main/login/')

def Historical_transactions(request):
    if 'user_id' in request.session:
        i = request.session['user_id']
        f = models.Transaction.objects.filter(id=i)
    else:
        return redirect('/main/login/')

    return render(request,'Historical_transactions.html')

def Purchase_record(request):
    if 'user_id' in request.session:
        i = request.session['user_id']
        f = models.Transaction.objects.filter(Buyer_id=i)
        b = models.user_information.objects.all()
        return render(request, 'Purchase_record.html',{'ff':f,'bb':b})
    else:
        return redirect('/main/login/')

def Sale_record(request):
    if 'user_id' in request.session:
        i = request.session['user_id']
        f = models.Transaction.objects.filter(Seller_id=i)
        b = models.user_information.objects.all()
        return render(request,'Sale_record.html',{'ff':f,'bb':b})
    else:
        return redirect('/main/login/')

def logout(request):
#实现退出功能
#删除session
    if 'user_id' in request.session:
        print("yunxing")
        if 'user_id' in request.session:
            del request.session['user_id']
            resp = HttpResponseRedirect('/main')
#删除cookie
        if 'user_id' in request.COOKIES:
            resp.delete_cookie('user_id')
        return resp
    else:
        return redirect('/main/login/')

#编写视图函数映射关系
    #urlpatterns = [
    #http://127.0.0.1:8000/user/logout
    #path('logout/', views.logout_view)]'''
q='com'
def manage_goods(request):
    if 'user_id' in request.session:
        global q
        i = request.session['user_id']
        b=models.goods_information.objects.filter(User_id=i)
        if request.method == "POST":
            a1=request.POST.get("good")
            if len(a1)!=0:
                q=a1
                return redirect("change_goods_information/")
        return render(request,'manage_goods.html',{'bb':b})
    else:
        return redirect('/main/login/')

def change_goods_information(request):
    if 'user_id' in request.session:
        s = q
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)
        b = models.goods_information.objects.filter(id=num).first()
        if request.method == "POST":
            a1=request.POST.get("down")
            models.goods_information.objects.filter(id=num).delete()
            return redirect("/main/goods/manage_goods/")
        return render(request,'change_goods_information.html',{'bb':b})
    else:
        return redirect('/main/login/')

g_id='com'
def Transaction_message(request):
    if 'user_id' in request.session:
    #goods_information表中的State为0时商品在主页展示没人买，

        i = request.session['user_id']
        b = models.goods_information.objects.filter(User_id=i).all()
        my_Transaction = models.Transaction.objects.filter(Seller_id = i).all()
        if request.method == "POST":
            global g_id
            g_id = request.POST.get("g_id")
            if g_id:
                return redirect('/main/Transaction_message/deal_transaction/')

        return render(request,'Transaction_message.html',{'bb': b , 'my_T': my_Transaction})

    else:
        return redirect('/main/login/')

def deal_transaction(request):
    if 'user_id' in request.session:
        iii = request.session['user_id']
        s = g_id
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)
        r = models.goods_information.objects.filter(id=num).first()
        if request.method == "POST":
            yes = request.POST.get("yes")#点接受订单返回1否则空
            no = request.POST.get("no")#点拒绝订单返回2否则空空
            if yes == "1":
                res3 = models.goods_information.objects.filter(id=num).update(State=2)
                success=1
                buyerID=models.shopping_cart.objects.filter(Goods_id=num).filter(State="2").first().User_id
                # res2 = models.Transaction.objects.create(Goods_id=num, Buyer_id=buyerID, Seller_id=iii,Buyer_offer=r.Peice, Seller_offer=r.Peice,if_success=success)
                try:
                    models.Transaction.objects.filter(if_success=0).filter(Goods_id=num).update(if_success=success)
                except:
                    print("更新失败")
                return redirect('/main/Transaction_message/')
            if no == "2":
                res3 = models.goods_information.objects.filter(id=num).update(State=0)
                fail=2
                buyerID = models.shopping_cart.objects.filter(Goods_id=num).filter(State="2").first().User_id
                # res2 = models.Transaction.objects.create(Goods_id=num, Buyer_id=buyerID, Seller_id=iii,Buyer_offer=r.Peice, Seller_offer=r.Peice, if_success=fail)
                try:
                    models.Transaction.objects.filter(if_success=0).filter(Goods_id=num).update(if_success=fail)
                except:
                    print("更新失败")
                return redirect('/main/Transaction_message/')
        return render(request, 'deal_transaction.html',{'i':r})
    else:
        return redirect('/main/login/')

def Shopping_Cart(request):
    if 'user_id' in request.session:
        ii = request.session['user_id']
        r = models.shopping_cart.objects.all()
        good = models.goods_information.objects.all()
        human = models.user_information.objects.all()
        if request.method == "POST":
            yes = request.POST.get("cha")#点查看订单返回1否则空
            no = request.POST.get("qu")#点取消收藏返回2否则空空
            if yes:
                global d
                d=yes
                s = d
                s = s[::-1]
                num = 0
                for i, v in enumerate(s):
                    for j in range(0, 10):
                        if v == str(j):
                            num += j * (10 ** i)
                models.shopping_cart.objects.filter(Goods_id=num).filter(User_id=ii).update(State=2)
                return redirect("/main/buy/")
            if no:
                s = no
                s = s[::-1]
                num = 0
                for i, v in enumerate(s):
                    for j in range(0, 10):
                        if v == str(j):
                            num += j * (10 ** i)
                models.shopping_cart.objects.filter(id = num).delete()
                return redirect('/main/Shopping_Cart/')
        s = ii
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)
        return render(request,'Shopping_Cart.html',{'rr':r,'goods':good,'humans':human,'now_user':num})
    else:
        return redirect('/main/login/')

def Modify_good_price(request):
    if 'user_id' in request.session:
        res = models.goods_information.objects.all()
    # s=request.session["user_id"]
    # print(s)
        s = q
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)
    # 修改商品名称
        if request.method == "POST":
            newprice = request.POST.get("good_price")
            model_information = models.goods_information.objects
            if newprice:
                res2 = model_information.filter(id=num).update(Peice=newprice)
                print("修改成功")
        return render(request, 'Modify_good_price.html', {'name_': res, 'ss': num})
    else:
        return redirect('/main/login/')

def Modify_good_name(request):
    if 'user_id' in request.session:
        res = models.goods_information.objects.all()
    # s=request.session["user_id"]
    # print(s)
        s = q
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)
    # 修改商品名称
        if request.method == "POST":
            newname = request.POST.get("good_name")
            model_information = models.goods_information.objects
            if newname:
                res2 = model_information.filter(id=num).update(Goods_name=newname)
                print("修改成功")
        return render(request, 'Modify_good_name.html', {'name_': res, 'ss': num})
    else:
        return redirect('/main/login/')

def Modify_good_description(request):
    if 'user_id' in request.session:
        res = models.goods_information.objects.all()
    # s=request.session["user_id"]
    # print(s)
        s = q
        s = s[::-1]
        num = 0
        for i, v in enumerate(s):
            for j in range(0, 10):
                if v == str(j):
                    num += j * (10 ** i)
    # 修改商品名称
        if request.method == "POST":
            newdescription = request.POST.get("good_description")
            model_information = models.goods_information.objects
            if newdescription:
                res2 = model_information.filter(id=num).update(Decription=newdescription)
                print("修改成功")
        return render(request, 'Modify_good_description.html', {'name_': res, 'ss': num})
    else:
        return redirect('/main/login/')

def tset(request):
    max_id = models.user_password.objects.aggregate(Max('id'))
    id = max_id['id__max']
    request.session["user_id"] = id
    request.COOKIES["user_id"] = id
    return render(request,'picturetest.html',{'max':id})


# 上传图片


