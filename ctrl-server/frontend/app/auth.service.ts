import { Injectable } from "@angular/core";
import { Http, Headers } from "@angular/http";

import 'rxjs/add/operator/map';

@Injectable()
export class AuthService
{
    private loggedIn = false;

    constructor(private http: Http)
    {
        this.loggedIn = !!localStorage.getItem("logged_in") && localStorage.getItem("logged_in") == "1";

        var self = this;

        this.authStatus().subscribe((res) => {
            localStorage.setItem("logged_in", res ? "1" : "0");
            self.loggedIn = res;
        });
    }

    private authStatus()
    {
        return this.http.post("/loggedIn", null, {}).map(res => res.json).map((res) => {
            return res["okay"];
        });
    }
}
