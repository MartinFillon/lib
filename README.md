# lib

Just a cpp lib that I use for school.
If you are from my shool don't use it or you get caught.

## How to use the ArgsParser

The args parser uses a json file to configure it
### Exemple file :

```json
{
    "Name": "bin",
    "Version": 0.1,
    "args": [
        {
            "name": "long",
            "description": "test arg",
            "required": true,
            "hasValue": false,
            "Short": "l"
        }
    ]
}
```

This file will be used to generate `--help` `--version` and to parse the args
