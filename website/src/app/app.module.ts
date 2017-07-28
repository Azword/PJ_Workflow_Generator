import {NgModule}       from '@angular/core';
import {BrowserModule}  from '@angular/platform-browser';
import {FormsModule}    from '@angular/forms';

import {AppComponent}         from './app.component';
import {AppRoutingModule} from "./app-routing.module";
import {HttpModule} from "@angular/http";
import {HomeComponent} from "./home/home.component";

@NgModule({
    imports: [
        BrowserModule,
        FormsModule,
        AppRoutingModule,
        HttpModule

    ],
    declarations: [
        AppComponent,
      HomeComponent
    ],
    providers: [],
    bootstrap: [AppComponent]
})
export class AppModule {
}
