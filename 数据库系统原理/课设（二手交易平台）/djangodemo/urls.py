"""djangodemo URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from app_demo import views
from django.conf.urls.static import static
from django.conf import settings
urlpatterns = [
    path('admin/', admin.site.urls),
    path('main/',views.newmain),
    path('login/main/', views.main),
    path('main/buy/', views.buy),
    path('main/login/', views.login, name='login'),
    path('main/register/', views.register, name = 'register'),
    path('login/main/change_my_information/', views.change_my_information,name = 'change_my_information'),
    path('main/personal_information/change_my_name/', views.change_my_name, name = 'change_my_name'),
    path('main/personal_information/change_my_telephone/', views.change_my_telephone, name = 'change_my_telephone'),
    path('main/personal_information/change_my_QQNumber/', views.change_my_QQNumber, name = 'change_my_QQNumber'),
    path('main/personal_information/change_my_gender/', views.change_my_gender, name='change_my_gender'),
    path('main/goods/put_goods/', views.put_goods, name = 'put_goods'),
    path('main/goods/',views.goods,name='goods'),
    path('main/personal_information/',views.personal_information,name='personal_information'),
    path('main/buy/transaction/',views.transaction,name='transaction'),
    path('main/Account_management/',views.Account_management,name='Account_management'),
    path('main/Account_management/change_password/',views.change_password,name='change_password'),
    path('main/Historical_transactions/',views.Historical_transactions,name='Historical_transactions'),
    path('main/Historical_transactions/Purchase_record/',views.Purchase_record,name='Purchase_record'),
    path('main/Historical_transactions/Sale_record/',views.Sale_record,name='Sale_record'),
    path('main/Account_management/logout/',views.logout,name='logout'),
    path('main/goods/manage_goods/',views.manage_goods,name='manage_goods'),
    path('main/goods/manage_goods/change_goods_information/',views.change_goods_information,name='change_goods_information'),
    path('main/Transaction_message/',views.Transaction_message,name='Transaction_message'),
    path('main/Shopping_Cart/',views.Shopping_Cart,name='Shopping_Cart'),
    path('main/goods/manage_goods/change_goods_information/Modify_good_name/',views.Modify_good_name,name='Modify_good_name'),
    path('main/goods/manage_goods/change_goods_information/Modify_good_description/',views.Modify_good_description,name='Modify_good_description'),
    path('main/goods/manage_goods/change_goods_information/Modify_good_price/',views.Modify_good_price,name='Modify_good_price'),
    path('main/Transaction_message/deal_transaction/',views.deal_transaction,name='deal_transaction'),
    path('test/',views.tset,name = 'test'),
    path('upload/', views.UpLoadInfo),
]+ static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)