import { platformBrowserDynamic } from '@angular/platform-browser-dynamic';
import { AppModule } from './modules/app';

const platform = platformBrowserDynamic();
platform.bootstrapModule(AppModule);
