import {Component} from '@angular/core';

@Component({
    selector: 'app',
    template: `
        <nav>
            <a routerLink="/home" routerLinkActive="active">Accueil</a>
        </nav>
        <router-outlet></router-outlet>
    `,
    styleUrls: ['./app.component.css'],
})
export class AppComponent {
}
