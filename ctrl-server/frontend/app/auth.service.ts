import { Injectable } from "@angular/core";
import { Http, Headers } from "@angular/http";

import 'rxjs/add/operator/map';

export class UserData
{
    constructor(public loggedIn: boolean, public username?: string, public email?: string)
    {

    }
}

@Injectable()
export class AuthService
{
    constructor(private http: Http)
    {
    }

    public getLoginStatus()
    {
        return this.http.get("/loginStatus").map(res => res.json).map((res) => {
            return new UserData(res["loggedIn"], res["user"], res["email"]);
        });
    }
}
