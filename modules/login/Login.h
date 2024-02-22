#pragma once

namespace login
{
    /**
     * @brief 登录类型
     *
     */
    enum LoginType
    {
        jwt
    };

    class Login
    {
    private:
        /* data */
    public:
        Login(/* args */);
        virtual ~Login();
        void doLogin();
    };
} // namespace login
