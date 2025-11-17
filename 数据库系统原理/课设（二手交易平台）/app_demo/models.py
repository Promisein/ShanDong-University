from django.db import models

# Create your models here.
# class UserInfo(models.Model):
#     name = models.CharField(max_length=32)
#     password = models.CharField(max_length=32)
#     age = models.IntegerField(default=100)
#     # data = models.IntegerField(null= True, blank=True)   # 可以为空
# '''
# create table app_demo_userinfo(
#        id bigint auto_increment primary key,
#        varchar(32),
#        varchar(32),
#        int
# );
# '''
# # 一定要注册自己app，不然不会将SQL语句提交到mysql数据库
# # python manage.py makemigrations
# # python manage.py migrate
# # 如果想要删除对应的表，直接把表的结构的类给注释掉即可，表中的结构也是同理
# # 直接增加列的话，手动写默认值
# class Department(models.Model):
#     title = models.CharField(max_length=16)
#
# # class ROle(models.Model):
# #     caption = models.CharField(max_length=16)
#
#
# # 新建数据等于sql的插入语句  insert into app_demo_department(title) values ("销售部")
# # Department.object.create(title="销售部")
#
# # UserInfo.objects.create(name = "刘于东", password = "123123", age = 19)


class user_password(models.Model):
    # id 是自然生成的
    password = models.CharField(max_length=20)

class user_information(models.Model):
    # 同时更新password的id
    name = models.CharField(max_length=20)
    gender = models.CharField(max_length=1)
    Telephone = models.CharField(max_length=11)
    Registration_time = models.DateTimeField(auto_now=True)
    QQ_number = models.CharField(max_length = 15)

class goods_information(models.Model):
    # Goods id 自动生成
    Goods_name = models.CharField(max_length=20)
    User_id = models.BigIntegerField()
    Peice = models.FloatField()
    Label_id = models.BigIntegerField()
    Decription = models.CharField(max_length=100)  # 各人描述的商品最多100字
    State = models.CharField(max_length=1, default="0")
    # 这里可能要增加一个商品的图片信息，来实现功能

class label(models.Model):
    # label 的 id 自动生成
    name = models.CharField(max_length=20)

# 购物车信息
class shopping_cart(models.Model):
    User_id = models.BigIntegerField()
    Goods_id = models.BigIntegerField()
    State = models.CharField(max_length=1)
    # 此时的states 和goods的states 可能不是一个信息，但是要保证能过同时更新

class Transaction(models.Model):
    # id 这里用自动生成的，可能后面用前端显示出来的加上1w比如 100001
    Buyer_id = models.BigIntegerField()
    Seller_id = models.BigIntegerField()
    Goods_id = models.BigIntegerField()
    Start_time = models.DateTimeField(auto_now_add =True)
    End_time = models.DateTimeField(auto_now=True)
    if_success = models.CharField(max_length=1)
    Buyer_offer = models.FloatField()
    Seller_offer = models.FloatField()

from .storage import ImageStorage

class Avatar(models.Model):
    user = models.CharField(max_length=100)
    photo = models.ImageField(upload_to='img', default='avatar.jpg', storage = ImageStorage())


#
# # 商品信息
# class GoodsInfo(models.Model):
#     # gpic = models.ImageField(upload_to='article_img/',verbose_name='商品图片',null=True,blank=True)
#     gpic = models.ImageField(upload_to='photos', storage=ImageStorage(), verbose_name='商品图片', null=True,
#                              blank=True)









