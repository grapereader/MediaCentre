import { NgModule }      from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { RouterModule } from '@angular/router';

import { AppComponent } from './app.component';
import { HomeComponent } from './home.component';
import { LoginComponent } from './login.component';

@NgModule({
    imports:      [
        BrowserModule,
        RouterModule.forRoot([
            {
                path: '',
                component: HomeComponent
            },
            {
                path: 'login',
                component: LoginComponent
            }
        ])
    ],
    declarations: [ AppComponent, LoginComponent, HomeComponent ],
    bootstrap:    [ AppComponent ]
})
export class AppModule { }
