from django.contrib import admin
from app_demo import  models
# Register your models here.
class ControllerTransaction(admin.ModelAdmin):
    list_display = ("id", "Buyer_id", "Seller_id", "Start_time","End_time", "if_success","Buyer_offer","Seller_offer","Goods_id")

    search_fields = ("id",)

admin.site.register(models.Transaction, ControllerTransaction)


class ControllerGoods(admin.ModelAdmin):
    list_display = ("id", "Goods_name", "User_id", "Peice", "Label_id","Decription","State")

    search_fields = ("id","Goods_name")

admin.site.register(models.goods_information, ControllerGoods)

class ControllerUser(admin.ModelAdmin):
    list_display = ("id", "password")

    search_fields = ("id",)

admin.site.register(models.user_password, ControllerUser)

class ControllerUser_information(admin.ModelAdmin):
    list_display = ("id", "name", "gender", "Telephone", "Registration_time", "QQ_number")

    search_fields = ("id",)

admin.site.register(models.user_information, ControllerUser_information)

class Controllerlabel(admin.ModelAdmin):
    list_display = ("id", "name")

    search_fields = ("id",)

admin.site.register(models.label, Controllerlabel)

class ControllerShopping_cart(admin.ModelAdmin):
    list_display = ("id", "User_id", "Goods_id", "State")

    search_fields = ("id",)

admin.site.register(models.shopping_cart, ControllerShopping_cart)