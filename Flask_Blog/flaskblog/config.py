import os

class Config:
    SECRET_KEY = "7fcc55351851eb50020ea3e187" #os.environ.get('SECRET_KEY')
    SQLALCHEMY_DATABASE_URI = "sqlite:///site.db" #os.environ.get('SQLALCHEMY_DATABASE_URI')
    MAIL_SERVER = 'smtp.gmail.com'
    MAIL_PORT = 465
    MAIL_USE_TLS = False
    MAIL_USE_SSL = True
    MAIL_USERNAME = 'dani98000k@gmail.com'#os.environ.get('EMAIL_USER')
    MAIL_PASSWORD = 'SBHNTHZK98'#os.environ.get('EMAIL_PASS')